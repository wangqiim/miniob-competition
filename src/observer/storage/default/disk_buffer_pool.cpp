/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Longda on 2021/4/13.
//
#include "disk_buffer_pool.h"
#include <errno.h>
#include <string.h>

#include "common/log/log.h"

using namespace common;

unsigned long current_time()
{
  struct timespec tp;
  clock_gettime(CLOCK_MONOTONIC, &tp);
  return tp.tv_sec * 1000 * 1000 * 1000UL + tp.tv_nsec;
}

Frame *BPManager::alloc() {
  FrameId frame_id;
  if (!free_list_.empty()) {
    frame_id = free_list_.front();
    free_list_.pop_front();
  } else {
    if (!replacer_->Victim(&frame_id)) {
      return nullptr;
    }
    DeletePageTable(frames_[frame_id].file_desc, frames_[frame_id].page.page_num);
  }
  replacer_->Pin(frame_id);
  return &frames_[frame_id];
}

Frame *BPManager::get(int file_desc, PageNum page_num) {
  if (page_table_.count(file_desc) != 0 && page_table_[file_desc].count(page_num) != 0) {
    return &frames_[page_table_[file_desc][page_num]];
  }
  return nullptr;
}

void BPManager::deleteFrame(FileDesc fd, PageNum pn, FrameId frame_id) {
  //这里pin一次，是为了防止被最后一次unpin之后delete，导致该frame既在lru中，又在free_lis中的严重bug
  replacer_->Pin(frame_id);
  DeletePageTable(fd, pn);
  free_list_.push_back(frame_id);
}

void BPManager::AddPageTable(FileDesc fd, PageNum pn, FrameId frame_id) {
  if (page_table_.count(fd) == 0) {
    page_table_[fd] = {};
  }  
  page_table_[fd][pn] = frame_id;
}

void BPManager::DeletePageTable(FileDesc fd, PageNum pn) {
  page_table_[fd].erase(pn);
  if (page_table_[fd].empty()) {
    page_table_.erase(fd);
  }
}

DiskBufferPool *theGlobalDiskBufferPool()
{
  static DiskBufferPool *instance = new DiskBufferPool();

  return instance;
}

RC DiskBufferPool::create_file(const char *file_name)
{
  int fd = open(file_name, O_RDWR | O_CREAT | O_EXCL, S_IREAD | S_IWRITE);
  if (fd < 0) {
    LOG_ERROR("Failed to create %s, due to %s.", file_name, strerror(errno));
    return RC::SCHEMA_DB_EXIST;
  }

  close(fd);

  /**
   * Here don't care about the failure
   */
  fd = open(file_name, O_RDWR);
  if (fd < 0) {
    LOG_ERROR("Failed to open for readwrite %s, due to %s.", file_name, strerror(errno));
    return RC::IOERR_ACCESS;
  }

  Page page;
  memset(&page, 0, sizeof(Page));

  BPFileSubHeader *fileSubHeader;
  fileSubHeader = (BPFileSubHeader *)page.data;
  fileSubHeader->allocated_pages = 1;
  fileSubHeader->page_count = 1;

  char *bitmap = page.data + (int)BP_FILE_SUB_HDR_SIZE;
  bitmap[0] |= 0x01;
  if (lseek(fd, 0, SEEK_SET) == -1) {
    LOG_ERROR("Failed to seek file %s to position 0, due to %s .", file_name, strerror(errno));
    close(fd);
    return RC::IOERR_SEEK;
  }

  if (write(fd, (char *)&page, sizeof(Page)) != sizeof(Page)) {
    LOG_ERROR("Failed to write header to file %s, due to %s.", file_name, strerror(errno));
    close(fd);
    return RC::IOERR_WRITE;
  }

  close(fd);
  LOG_INFO("Successfully create %s.", file_name);
  return RC::SUCCESS;
}

RC DiskBufferPool::drop_file(const char *file_name) {
  
  int fd = ::unlink(file_name);
  if (-1 == fd) {
    return RC::IOERR;
  }
  LOG_INFO("Successfully drop %s.", file_name);
  return RC::SUCCESS;
}

RC DiskBufferPool::open_file(const char *file_name, int *file_id)
{
  if (file_name == nullptr) {
    return RC::BUFFERPOOL_FILEERR;
  }
  int fd;
  // This part isn't gentle, the better method is using LRU queue.
  if (file_name_id_.count(file_name) != 0) {
    *file_id = file_name_id_[file_name];
    LOG_INFO("%s has already been opened.", file_name);
    return RC::SUCCESS;
  }

  if (free_file_ids_.size() == 0) {
    LOG_ERROR("Failed to open file %s, because too much files has been opened.", file_name);
    return RC::BUFFERPOOL_OPEN_TOO_MANY_FILES;
  }

  if ((fd = open(file_name, O_RDWR)) < 0) {
    LOG_ERROR("Failed to open file %s, because %s.", file_name, strerror(errno));
    return RC::IOERR_ACCESS;
  }
  LOG_INFO("Successfully open file %s.", file_name);

  BPFileHandle *file_handle = new (std::nothrow) BPFileHandle();
  if (file_handle == nullptr) {
    LOG_ERROR("Failed to alloc memory of BPFileHandle for %s.", file_name);
    close(fd);
    return RC::NOMEM;
  }
  RC tmp;
  file_handle->bopen = true;
  int file_name_len = strlen(file_name) + 1;
  char *cloned_file_name = new char[file_name_len];
  snprintf(cloned_file_name, file_name_len, "%s", file_name);
  cloned_file_name[file_name_len - 1] = '\0';
  file_handle->file_name = cloned_file_name;
  file_handle->file_desc = fd;
  if ((tmp = allocate_block(&file_handle->hdr_frame)) != RC::SUCCESS) {
    LOG_ERROR("Failed to allocate block for %s's BPFileHandle.", file_name);
    delete file_handle;
    close(fd);
    return tmp;
  }
  file_handle->hdr_frame->dirty = false;
  file_handle->hdr_frame->file_desc = fd;
  file_handle->hdr_frame->pin_count = 1;
  if ((tmp = load_page(0, file_handle, file_handle->hdr_frame)) != RC::SUCCESS) {
    file_handle->hdr_frame->pin_count = 0;
    // 在dispose_block中去清楚bpm的frame元信息
    dispose_block(file_handle->hdr_frame);
    close(fd);
    delete file_handle;
    return tmp;
  }
  bp_manager_.AddPageTable(fd, 0, bp_manager_.GetFrameID(file_handle->hdr_frame));

  file_handle->hdr_page = &(file_handle->hdr_frame->page);
  file_handle->bitmap = file_handle->hdr_page->data + BP_FILE_SUB_HDR_SIZE;
  file_handle->file_sub_header = (BPFileSubHeader *)file_handle->hdr_page->data;
  
  int open_index = free_file_ids_.front();
  free_file_ids_.pop_front();
  open_file_[open_index] = file_handle;
  file_name_id_[file_name] = open_index;
  *file_id = open_index;
  LOG_INFO("Successfully open %s. file_id=%d, hdr_frame=%p", file_name, *file_id, file_handle->hdr_frame);
  return RC::SUCCESS;
}

RC DiskBufferPool::close_file(int file_id)
{
  RC tmp;
  if ((tmp = check_file_id(file_id)) != RC::SUCCESS) {
    LOG_ERROR("Failed to close file, due to invalid fileId %d", file_id);
    return tmp;
  }

  BPFileHandle *file_handle = open_file_[file_id];
  file_handle->hdr_frame->pin_count--;
  if ((tmp = force_all_pages(file_handle)) != RC::SUCCESS) {
    file_handle->hdr_frame->pin_count++;
    LOG_PANIC("Failed to closeFile %d:%s, due to failed to force all pages.", file_id, file_handle->file_name);
    return tmp;
  }

  if (close(file_handle->file_desc) < 0) {
    LOG_ERROR("Failed to close fileId:%d, fileName:%s, error:%s", file_id, file_handle->file_name, strerror(errno));
    return RC::IOERR_CLOSE;
  }
  free_file_ids_.push_back(file_id);
  open_file_.erase(file_id);
  file_name_id_.erase(file_handle->file_name);
  delete (file_handle);
  LOG_INFO("Successfully close file %d:%s.", file_id, file_handle->file_name);
  return RC::SUCCESS;
}

RC DiskBufferPool::get_this_page(int file_id, PageNum page_num, BPPageHandle *page_handle)
{
  RC tmp;
  if ((tmp = check_file_id(file_id)) != RC::SUCCESS) {
    LOG_ERROR("Failed to load page %d, due to invalid fileId %d", page_num, file_id);
    return tmp;
  }

  BPFileHandle *file_handle = open_file_[file_id];
  if ((tmp = check_page_num(page_num, file_handle)) != RC::SUCCESS) {
    LOG_ERROR("Failed to load page %s:%d, due to invalid pageNum.", file_handle->file_name, page_num);
    return tmp;
  }

  // This page has been loaded.
  if (bp_manager_.get(file_handle->file_desc, page_num) != nullptr) {
    page_handle->frame = bp_manager_.get(file_handle->file_desc, page_num);
    page_handle->frame->pin_count++;
    bp_manager_.replacer_->Pin(bp_manager_.GetFrameID(page_handle->frame));
    page_handle->open = true;
    return RC::SUCCESS;
  }

  // Allocate one page and load the data into this page
  if ((tmp = allocate_block(&(page_handle->frame))) != RC::SUCCESS) {
    LOG_ERROR("Failed to load page %s:%d, due to failed to alloc page.", file_handle->file_name, page_num);
    return tmp;
  }
  page_handle->frame->dirty = false;
  page_handle->frame->file_desc = file_handle->file_desc;
  page_handle->frame->pin_count = 1;
  if ((tmp = load_page(page_num, file_handle, page_handle->frame)) != RC::SUCCESS) {
    LOG_ERROR("Failed to load page %s:%d", file_handle->file_name, page_num);
    page_handle->frame->pin_count = 0;
    dispose_block(page_handle->frame);
    return tmp;
  }
  bp_manager_.AddPageTable(file_handle->file_desc, page_num, bp_manager_.GetFrameID(page_handle->frame));

  page_handle->open = true;
  return RC::SUCCESS;
}

RC DiskBufferPool::allocate_page(int file_id, BPPageHandle *page_handle)
{
  RC tmp;
  if ((tmp = check_file_id(file_id)) != RC::SUCCESS) {
    LOG_ERROR("Failed to alloc page, due to invalid fileId %d", file_id);
    return tmp;
  }

  BPFileHandle *file_handle = open_file_[file_id];

  int byte = 0, bit = 0;
  if ((file_handle->file_sub_header->allocated_pages) < (file_handle->file_sub_header->page_count)) {
    // There is one free page
    for (int i = 0; i < file_handle->file_sub_header->page_count; i++) {
      byte = i / 8;
      bit = i % 8;
      if (((file_handle->bitmap[byte]) & (1 << bit)) == 0) {
        (file_handle->file_sub_header->allocated_pages)++;
        file_handle->bitmap[byte] |= (1 << bit);
        return get_this_page(file_id, i, page_handle);
      }
    }
  }

  if ((tmp = allocate_block(&(page_handle->frame))) != RC::SUCCESS) {
    LOG_ERROR("Failed to allocate page %s, due to no free page.", file_handle->file_name);
    return tmp;
  }

  PageNum page_num = file_handle->file_sub_header->page_count;
  file_handle->file_sub_header->allocated_pages++;
  file_handle->file_sub_header->page_count++;

  byte = page_num / 8;
  bit = page_num % 8;
  file_handle->bitmap[byte] |= (1 << bit);
  file_handle->hdr_frame->dirty = true;

  page_handle->frame->dirty = false;
  page_handle->frame->file_desc = file_handle->file_desc;
  page_handle->frame->pin_count = 1;
  page_handle->frame->acc_time = current_time();
  memset(&(page_handle->frame->page), 0, sizeof(Page));
  page_handle->frame->page.page_num = file_handle->file_sub_header->page_count - 1;


  bp_manager_.AddPageTable(file_handle->file_desc, page_handle->frame->page.page_num, bp_manager_.GetFrameID(page_handle->frame));
  
  // fileSubHeader的page_count数量变化了应该立即刷新到磁盘
  if ((tmp = flush_block(file_handle->hdr_frame)) != RC::SUCCESS) {
    LOG_ERROR("DiskBufferPool::allocate_page Failed to flush_block.");
    return tmp;
  }
  // Use flush operation to extion file
  if ((tmp = flush_block(page_handle->frame)) != RC::SUCCESS) {
    LOG_ERROR("Failed to alloc page %s , due to failed to extend one page.", file_handle->file_name);
    return tmp;
  }

  page_handle->open = true;
  return RC::SUCCESS;
}

RC DiskBufferPool::get_page_num(BPPageHandle *page_handle, PageNum *page_num)
{
  if (!page_handle->open)
    return RC::BUFFERPOOL_CLOSED;
  *page_num = page_handle->frame->page.page_num;
  return RC::SUCCESS;
}

RC DiskBufferPool::get_data(BPPageHandle *page_handle, char **data)
{
  if (!page_handle->open)
    return RC::BUFFERPOOL_CLOSED;
  *data = page_handle->frame->page.data;
  return RC::SUCCESS;
}

RC DiskBufferPool::mark_dirty(BPPageHandle *page_handle)
{
  page_handle->frame->dirty = true;
  return RC::SUCCESS;
}

RC DiskBufferPool::unpin_page(BPPageHandle *page_handle)
{
  page_handle->open = false;
  page_handle->frame->pin_count--;
  if (page_handle->frame->pin_count == 0) {
    bp_manager_.replacer_->Unpin(bp_manager_.GetFrameID(page_handle->frame));
  }
  return RC::SUCCESS;
}


/**
 * dispose_page will delete the data of the page of pageNum
 * force_page will flush the page of pageNum
 * @param fileID
 * @param pageNum
 * @return
 */
RC DiskBufferPool::dispose_page(int file_id, PageNum page_num)
{
  RC rc;
  if ((rc = check_file_id(file_id)) != RC::SUCCESS) {
    LOG_ERROR("Failed to alloc page, due to invalid fileId %d", file_id);
    return rc;
  }

  BPFileHandle *file_handle = open_file_[file_id];
  if ((rc = check_page_num(page_num, file_handle)) != RC::SUCCESS) {
    LOG_ERROR("Failed to dispose page %s:%d, due to invalid pageNum", file_handle->file_name, page_num);
    return rc;
  }
  Frame *frame = bp_manager_.get(file_handle->file_desc, page_num);
  if (frame == nullptr) {
    return RC::BUFFERPOOL_PAGE_PINNED;
  }
  if (frame->pin_count != 0) {
    return RC::BUFFERPOOL_PAGE_PINNED;
  }

  bp_manager_.deleteFrame(file_handle->file_desc, page_num, bp_manager_.GetFrameID(frame));
  
  file_handle->hdr_frame->dirty = true;
  file_handle->file_sub_header->allocated_pages--;
  // file_handle->pFileSubHeader->pageCount--;
  char tmp = 1 << (page_num % 8);
  file_handle->bitmap[page_num / 8] &= ~tmp;
  return RC::SUCCESS;
}


RC DiskBufferPool::force_page(int file_id, PageNum page_num)
{
  RC rc;
  if ((rc = check_file_id(file_id)) != RC::SUCCESS) {
    LOG_ERROR("Failed to alloc page, due to invalid fileId %d", file_id);
    return rc;
  }
  BPFileHandle *file_handle = open_file_[file_id];
  return force_page(file_handle, page_num);
}

/**
 * dispose_page will delete the data of the page of pageNum
 * force_page will flush the page of pageNum
 * force_page != flush_page
 * @param fileHandle
 * @param pageNum
 * @return
 */
RC DiskBufferPool::force_page(BPFileHandle *file_handle, PageNum page_num)
{
  if (page_num == -1) {
    Frame *frame;
    std::vector<std::pair<int, int>> deleted_pages;
    for (auto &it : bp_manager_.page_table_[file_handle->file_desc]) {
      frame = &bp_manager_.frames_[it.second];
      if (frame->pin_count != 0) {
        LOG_ERROR("Page :%s:%d has been pinned.", file_handle->file_name, page_num);
        return RC::BUFFERPOOL_PAGE_PINNED;
      }
      if (frame->dirty) {
        RC rc = RC::SUCCESS;
        if ((rc = flush_block(frame)) != RC::SUCCESS) {
          LOG_ERROR("Failed to flush page:%s:%d.", file_handle->file_name, page_num);
          return rc;
        }
      }
      deleted_pages.push_back({it.first, it.second});
    }
    
    for (auto &it : deleted_pages) {
      RC rc = flush_block(&bp_manager_.frames_[it.second]);
      bp_manager_.deleteFrame(file_handle->file_desc, it.first, it.second);
    }
    return RC::SUCCESS;
  }
  Frame *frame = bp_manager_.get(file_handle->file_desc, page_num);
  if (frame == nullptr) {
    // 对齐原版本，原版本：如果在located数组中找不到对应的已经分配的frame也返回success
    // return RC::BUFFERPOOL_PAGE_PINNED;
    return RC::SUCCESS;
  }
  if (frame->pin_count != 0) {
    LOG_ERROR("Page :%s:%d has been pinned.", file_handle->file_name, page_num);
    return RC::BUFFERPOOL_PAGE_PINNED;
  }
  if (frame->dirty) {
    RC rc = RC::SUCCESS;
    if ((rc = flush_block(frame)) != RC::SUCCESS) {
      LOG_ERROR("Failed to flush page:%s:%d.", file_handle->file_name, page_num);
      return rc;
    }
  }
  bp_manager_.deleteFrame(file_handle->file_desc, page_num, bp_manager_.GetFrameID(frame));
  return RC::SUCCESS;
}

RC DiskBufferPool::flush_all_pages(int file_id)
{
  RC rc = check_file_id(file_id);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to flush pages due to invalid file_id %d", file_id);
    return rc;
  }

  BPFileHandle *file_handle = open_file_[file_id];
  // TODO(wq): 这里应该是flush所有的页?为什么是force所有的页??
  return force_all_pages(file_handle);
}

RC DiskBufferPool::force_all_pages(BPFileHandle *file_handle)
{
  std::vector<std::pair<int, int>> deleted_pages;
  for (auto &it : bp_manager_.page_table_[file_handle->file_desc]) {
    if (bp_manager_.frames_[it.second].dirty) {
      deleted_pages.push_back({it.second, it.second});
      RC rc = flush_block(&bp_manager_.frames_[it.second]);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to flush all pages' of %s.", file_handle->file_name);
        return rc;
      }
    }
  }
  for (auto &it : deleted_pages) {
    RC rc = flush_block(&bp_manager_.frames_[it.second]);
    bp_manager_.deleteFrame(file_handle->file_desc, it.first, it.second);
  }
  return RC::SUCCESS;
}

RC DiskBufferPool::flush_block(Frame *frame)
{
  // The better way is use mmap the block into memory,
  // so it is easier to flush data to file.

  s64_t offset = ((s64_t)frame->page.page_num) * sizeof(Page);
  if (lseek(frame->file_desc, offset, SEEK_SET) == offset - 1) {
    LOG_ERROR("Failed to flush page %lld of %d due to failed to seek %s.", offset, frame->file_desc, strerror(errno));
    return RC::IOERR_SEEK;
  }

  if (write(frame->file_desc, &(frame->page), sizeof(Page)) != sizeof(Page)) {
    LOG_ERROR("Failed to flush page %lld of %d due to %s.", offset, frame->file_desc, strerror(errno));
    return RC::IOERR_WRITE;
  }
  frame->dirty = false;
  LOG_DEBUG("Flush block. file desc=%d, page num=%d", frame->file_desc, frame->page.page_num);

  return RC::SUCCESS;
}

RC DiskBufferPool::allocate_block(Frame **buffer)
{
  // There is one Frame which is free.
  Frame *frame = bp_manager_.alloc();
  if (frame == nullptr) {
    LOG_ERROR("All pages have been used and pinned.");
    return RC::NOMEM;
  }
  LOG_DEBUG("Allocate block frame=%p", frame);

  if (frame->dirty) {
    RC rc = flush_block(frame);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to flush block of %d for %d.",  bp_manager_.GetFrameID(frame), frame->file_desc);
      return rc;
    }
  }
  *buffer = frame;
  return RC::SUCCESS;
}

RC DiskBufferPool::dispose_block(Frame *buf)
{
  if (buf->pin_count != 0) {
    LOG_WARN("Begin to free page %d of %d, but it's pinned.", buf->page.page_num, buf->file_desc);
    return RC::LOCKED_UNLOCK;
  }
  if (buf->dirty) {
    RC rc = flush_block(buf);
    if (rc != RC::SUCCESS) {
      LOG_WARN("Failed to flush block %d of %d during dispose block.", buf->page.page_num, buf->file_desc);
      return rc;
    }
  }
  buf->dirty = false;
  
  bp_manager_.deleteFrame(buf->file_desc, buf->page.page_num, bp_manager_.GetFrameID(buf));
  LOG_DEBUG("dispost block frame =%p", buf);
  return RC::SUCCESS;
}

RC DiskBufferPool::check_file_id(int file_id)
{
  if (file_id < 0 || file_id >= MAX_OPEN_FILE) {
    LOG_ERROR("Invalid fileId:%d.", file_id);
    return RC::BUFFERPOOL_ILLEGAL_FILE_ID;
  }
  if (open_file_.count(file_id) == 0) {
    LOG_ERROR("Invalid fileId:%d, it is empty.", file_id);
    return RC::BUFFERPOOL_ILLEGAL_FILE_ID;
  }
  return RC::SUCCESS;
}

// needn't modify
RC DiskBufferPool::get_page_count(int file_id, int *page_count)
{
  RC rc = RC::SUCCESS;
  if ((rc = check_file_id(file_id)) != RC::SUCCESS) {
    return rc;
  }
  *page_count = open_file_[file_id]->file_sub_header->page_count;
  return RC::SUCCESS;
}

RC DiskBufferPool::check_page_num(PageNum page_num, BPFileHandle *file_handle)
{
  if (page_num >= file_handle->file_sub_header->page_count) {
    LOG_ERROR("Invalid pageNum:%d, file's name:%s", page_num, file_handle->file_name);
    return RC::BUFFERPOOL_INVALID_PAGE_NUM;
  }
  if ((file_handle->bitmap[page_num / 8] & (1 << (page_num % 8))) == 0) {
    LOG_ERROR("Invalid pageNum:%d, file's name:%s", page_num, file_handle->file_name);
    return RC::BUFFERPOOL_INVALID_PAGE_NUM;
  }
  return RC::SUCCESS;
}

// needn't modify
RC DiskBufferPool::load_page(PageNum page_num, BPFileHandle *file_handle, Frame *frame)
{
  s64_t offset = ((s64_t)page_num) * sizeof(Page);
  if (lseek(file_handle->file_desc, offset, SEEK_SET) == -1) {
    LOG_ERROR(
        "Failed to load page %s:%d, due to failed to lseek:%s.", file_handle->file_name, page_num, strerror(errno));

    return RC::IOERR_SEEK;
  }
  if (read(file_handle->file_desc, &(frame->page), sizeof(Page)) != sizeof(Page)) {
    LOG_ERROR(
        "Failed to load page %s:%d, due to failed to read data:%s.", file_handle->file_name, page_num, strerror(errno));
    return RC::IOERR_READ;
  }
  return RC::SUCCESS;
}

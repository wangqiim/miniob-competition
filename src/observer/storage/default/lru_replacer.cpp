#include "storage/default/lru_replacer.h"

LRUReplacer::LRUReplacer(size_t num_pages) : capacity_(num_pages) {
}

LRUReplacer::~LRUReplacer() = default;

bool LRUReplacer::Victim(FrameId *frame_id) {
  std::lock_guard<std::mutex> locker(latch);
  
  if (cache_list_.empty()) return false;

  *frame_id = cache_list_.back();
  cache_map_.erase(*frame_id);
  cache_list_.pop_back();

  return true;
}

void LRUReplacer::Pin(FrameId frame_id) {
  std::lock_guard<std::mutex> locker(latch);

  if (cache_map_.count(frame_id) != 0) {
    cache_list_.erase(cache_map_[frame_id]);
    cache_map_.erase(frame_id);
  }
}

void LRUReplacer::Unpin(FrameId frame_id) {
  std::lock_guard<std::mutex> locker(latch);

  if (cache_map_.count(frame_id) != 0) {
    return ;
  }

  while (Size() >= capacity_) {
    FrameId need_del = cache_list_.back();
    cache_list_.pop_back();
    cache_map_.erase(need_del);
  }

  cache_list_.push_front(frame_id);
  cache_map_[frame_id] = cache_list_.begin();
}

size_t LRUReplacer::Size() {
  return cache_list_.size();
}

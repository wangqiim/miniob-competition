#include "storage/default/lru_replacer.h"

LRUReplacer::LRUReplacer(size_t num_pages) : size_(0), capacity_(num_pages) {
  cache_map_.clear();
  cache_list_.clear();
}

LRUReplacer::~LRUReplacer() = default;

bool LRUReplacer::Victim(FrameId *frame_id) {
  if (this->size_ == 0) {
    return false;
  }
  FrameId back = cache_list_.back();
  this->cache_map_.erase(back);
  this->cache_list_.pop_back();
  *frame_id = back;
  this->size_--;
  return true;
}

void LRUReplacer::Pin(FrameId frame_id) {
  if (this->cache_map_.find(frame_id) != this->cache_map_.end()) {
    this->cache_list_.erase(this->cache_map_[frame_id]);
    this->cache_map_.erase(frame_id);
    this->size_--;
  }
}

void LRUReplacer::Unpin(FrameId frame_id) {
  if (this->cache_map_.find(frame_id) == this->cache_map_.end()) {
    this->cache_list_.push_front(frame_id);
    this->cache_map_[frame_id] = cache_list_.begin();
    this->size_++;
  }
  if (this->size_ > this->capacity_) {
    FrameId back = cache_list_.back();
    this->cache_list_.pop_back();
    this->cache_map_.erase(back);
    this->size_--;
  }
}

size_t LRUReplacer::Size() {
  return this->size_;
}

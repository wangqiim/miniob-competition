#include <list>
#include <unordered_map>
#include <vector>

#include "storage/default/replacer.h"
#include "storage/config.h"


/**
 * LRUReplacer implements the lru replacement policy, which approximates the Least Recently Used policy.
 */
class LRUReplacer : public Replacer {
 public:
  /**
   * Create a new LRUReplacer.
   * @param num_pages the maximum number of pages the LRUReplacer will be required to store
   */
  explicit LRUReplacer(size_t num_pages);

  /**
   * Destroys the LRUReplacer.
   */
  ~LRUReplacer() override;

  bool Victim(FrameId *frame_id) override;

  void Pin(FrameId frame_id) override;

  void Unpin(FrameId frame_id) override;

  size_t Size() override;

 private:
  std::unordered_map<FrameId, std::list<FrameId>::iterator> cache_map_;
  std::list<FrameId> cache_list_;  // from front to back: new -> old
  size_t size_;
  size_t capacity_;
};

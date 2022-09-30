#pragma once
#include <cstddef>
#include <forward_list>
#include <functional>
#include <vector>

namespace pr {
template <typename K, typename V>
class HashTable {
  class Entry {
   public:
    const K key;
    V value;
    Entry(const K& key, const V& value) : key(key), value(value) {}
  };
  typedef std::vector<std::forward_list<Entry>> buckets_t;
  buckets_t buckets;

 public:
  HashTable(size_t init = 100) { buckets.resize(init); }

  V* get(const K& key) {
    size_t h = std::hash<K>()(key);
    h = h % buckets.size();
    for (Entry& c : buckets[h]) {
      if (c.key == key) {
        return &c.value;
      }
    }
    return nullptr;
  }

  bool put(const K& key, const V& value) {
    size_t h = std::hash<K>()(key);
    h = h % buckets.size();
    for (Entry& c : buckets[h]) {
      if (c.key == key) {
        c.value = value;
        return true;
      }
    }
    buckets[h].emplace_front(Entry(key,value));
    return false;
  }
  size_t size() const { return buckets.size(); }
  void grow() {
    size_t old_size = buckets.size();
    HashTable n(old_size * 2);
    for (auto& l : buckets) {
      for (auto& el : l) {
        n.put(el.key, el.value);
      }
    }
    buckets.swap(n.buckets);
    n.buckets.clear();
  }
};
}  // namespace pr

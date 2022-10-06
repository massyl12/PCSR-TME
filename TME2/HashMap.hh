#pragma once
#include <vector>
#include <forward_list>

template<typename K,typename V>
class HashMap{
	class Entry{
		const K key;
		V value;
	};
	typedef std::vector<std::forward_list<Entry>> buckets_t;
	buckets_t buckets;
	HashMap(size_t init = 100){
		buckets.reserve(init);
		for(size_t i=0; i < buckets.size(); i++){
			std::forward_list<Entry> bucket = new std::forward_list<Entry>;
			buckets[i].push_back(bucket);
		}
		
	}

	V* get(const K &key){
		size_t h = std::hash<K>()(key);
		h = h % buckets.size();
		for(size_t i=0; i<buckets.size();i++){
			for(const Entry &entry : buckets[i]){
				if(entry.key == key){
					return entry.value;
				}
			}
		}
	}
};
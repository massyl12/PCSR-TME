/*
 * HashMap.h
 *
 *  Created on: 29 sept. 2023
 *      Author: 28633410
 */

// #pragma once
#ifndef HASHMAPTME2_H_
#define HASHMAPTME2_H_

#include <vector>
#include <forward_list>
#include <iterator>

using namespace std;

namespace pr {
	template <typename K, typename V>
	class HashMap {
		public: 
			class Entry {
				public: 
					const K key;
					V value;
					Entry(const K &k,const V& v):key(k),value(v){}
					operator pair<K,V>() const {
						return make_pair(key,value);
					}
			};
		private:

			size_t sz;
		public:
			vector<forward_list<Entry>> buckets;
			HashMap(size_t size) : sz(0) {
				buckets.reserve(size);
				for(size_t i=0; i<size ;i++){
					forward_list<Entry> list;
					buckets.push_back(list);
				}
			}
			V* get(const K & key) {
				size_t h = std::hash<K>()(key)%buckets.size();
				for( Entry& entry : buckets[h] ){
					if(entry.key==key){
						return &entry.value;
					}
				}
				return nullptr;
			}
			bool put (const K & key, const V & value) {
				size_t h = std::hash<K>()(key)%buckets.size();
				for( Entry& entry : buckets[h] ){
					if(entry.key==key){
						entry.value = value;
						return true;
					} 
				}
				sz++;
				buckets[h].push_front(Entry(key,value));
				return false;
			}
			size_t size() const {
				return sz;
			}
			void grow() {
				if(buckets.size()*0.8 <= sz){
					buckets.resize(buckets.size()*2);
				}
			}
	};
};

#endif /* HASHMAPTME2_H_ */


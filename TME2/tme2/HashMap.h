#ifndef HASHMAP_H
#define HASHMAP_H
#pragma once
#include <forward_list>
#include <vector>
#include <cstddef>

namespace pr{
    template <typename k,typename v>
    class HashMap{
        public: 
        class Entry{
            public:
            const k key;
            v value;
            Entry(const k& key,const v& value):key(key),value(value){}
        };
        private : 
        typedef std::vector<std::forward_list <Entry>>bucket_t;
        bucket_t buckets;
        size_t sz;
        public : 
        HashMap(size_t size):buckets(size),sz(0){}
        v* get(const k& key){
            size_t h=std::hash<k>()(key);
            size_t target=h%buckets.size();
            for(Entry& ent:buckets[target]){
                if(ent.key==key){
                    return &ent.value;
                }
            }
            return nullptr;
        }
        bool put (const k& key, const v& value){
            size_t h=std::hash<k>()(key);
            size_t target=h%buckets.size();

            for(auto& ent: buckets[target]){
                if(ent.key==key){
                    ent.value=value;
                    return true;
                }
            }
            
            buckets[target].push_front(Entry(key,value));
            sz++;
          
            return false;
            
        }
        size_t size() const{
            return sz;
        }
    };
}

#endif
//Question 5
#pragma once
#include <vector>
#include <forward_list>
namespace pr {

    template <typename K, typename V>

    class HashTable {

        public: 
            class Entry {
                public: 
                    const K key;
                    V val;
                
                    Entry (K key, V val):key(key), val(val){}
            };

            std::vector<std::forward_list<Entry>> bucket;
            size_t size_;

        
            HashTable (int size) {
                bucket.reserve(size);
                for(size_t i = 0;i<size;i++){
                    bucket.push_back(std::forward_list<Entry>());
                }
            }
            ~HashTable () {
                for (int i = 0; i < vec.size(); ++i) {
                    vec[i].clear();
                }
                vec.clear();
            }


            V * get (const K & key){
                size_t h = std::hash<K>()(key);
                size_t target = h % bucket.capacity();
                
                for (Entry &ent : bucket[target]){
                    if (ent.key  == key) {
                        return &ent.val;
                    }
                }

                
                return nullptr; //key not found
            }

           

            
            bool put (const K & key, const V & value) {
                
                //Mise à jour d'une valeur déjà existante
                V * val = get (key);
                if (val) {
                    *val = value;
                    return true;
                }

                //

                //Réalisation d'une insertion    
                size_t h = std::hash<K>()(key);
                size_t target = h % bucket.size();
                size_t size_++;

                bucket.push_front(Entry(key, value));
                return false;
            }

            size_t size () const {
                return size_;
            }

    };

    //fin du namespace
}

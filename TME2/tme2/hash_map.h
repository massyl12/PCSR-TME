#pragma once
#include <vector>
#include <forward_list>
namespace pr {

    template <typename K, V>

    class HashMap {

        class Entry {
            const K key;
            V val;

            Entry (K key, V val):key(key), val(val){}

            ~Entry () {
                delete key;
                delete val;
            }
        };

        std::vector<std::forward_list<Entry>> vec;

        HashMap (int size) {
            vec = new std::vector<std::forward_list<Entry>> (size,new std::forward_list<Entry>);
        }

        V * get (const K & key){
            size_t h = std::hash<K>()(key);
            size_t target = h % vec.size();
            std::forward_list<Entry> bucket = vec[target];
            /* for (Entry &ent : vec[target]){
                if (ent.key  == key) {
                    return &ent.val;
                }
            } */

            for (auto it = bucket.begin(); it != bucket.end(); ++it) {
                if (it->key == key) {
                    return &(it->val);
                }
            }
            return nullptr; //key not found
        } 

        bool put (const K & key, const V & value) {
            V * val = get (key);
            if (val) {
                *val = value;
                return true;
            }

            size_t h = std::hash<K>()(key);
            size_t target = h % vec.size();
            std::forward_list<Entry> bucket = vec[target];

            Entry * ent = new Entry(key, value);
            bucket.push_front(ent);
            return false;
        }

        size_t size () const {
            return vec.size();
        }

        ~HashMap () {
            delete [] vec;
        }

        void grow () {

        }
    }

    //fin du namespace
}
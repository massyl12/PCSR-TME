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

            std::vector<std::forward_list<Entry>> vec;

        
            HashTable (int size) {
                vec.reserve(size);
            }

            V * get (const K & key){
                size_t h = std::hash<K>()(key);
                size_t target = h % vec.capacity();
                std::forward_list<Entry> bucket = vec[target];
                for (Entry &ent : vec[target]){
                    if (ent.key  == key) {
                        return &ent.val;
                    }
                }

                /* for (auto it = bucket.begin(); it != bucket.end(); ++it) {
                    if (it->key == key) {
                        return &(it->val);
                    }
                } */
                return nullptr; //key not found
            }

            ~HashTable () {
                for (int i = 0; i < vec.size(); ++i) {
                    vec[i].clear();
                }
                vec.clear();
            }

            void grow () {
                //On alloue un nouveau vecteur avec le double de la taille actuelle
                std::vector<std::forward_list<Entry>> new_vec (vec.size()*2, std::forward_list<Entry>());

                //On ajoute dans les nouveau vecteur les éléments présents qui étaient déjà présents avant
                Entry * ent;
                for (int i = 0; i < vec.size(); ++i){
                    for (Entry & enti : vec[i]){

                        //On calcule le nouvel index (car la taille a changé)
                        size_t h = std::hash<K>()(enti.key);
                        size_t target = h % new_vec.size();
                        std::forward_list<Entry> bucket = vec[target];

                        ent = new Entry(enti.key, enti.val);
                        bucket.push_front(ent);
                    }
                } 

                //On supprime l'ancien vecteur
                ~HashTable<K,V>();

                vec = new_vec;
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
                size_t target = h % vec.size();
                std::forward_list<Entry> bucket = vec[target];

                bucket.push_front(Entry(key, value));
                return false;
            }

            size_t size () const {
                return vec.size();
            }

    };

    //fin du namespace
}

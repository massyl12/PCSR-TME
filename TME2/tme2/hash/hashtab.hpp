//
//  hashtab.hpp
//
//
//  Created by Harena Rakotondratsima on 29/09/2023.
//

#ifndef hashtab_hpp
#define hashtab_hpp

#include <iostream>
#include <vector>
#include <forward_list>
#include "generic.hpp"

//inlining method

using namespace std;
template <typename K,typename V>       //a l instanciation de la class HashMap je dois specifier le type de K et V ie => HashMap <string,int>


class HashMap{
    public :
    class Entry {
    public:
        K Key;
        V Value;
        Entry(const K Key,const V Value) : Key(Key),Value(Value){}
        
        Entry& operator=(const Entry& other){
            if(this!=&other){
                this->Key=other.Key;
                this->Value=other.Value;
            }
            return *this;
        }
        
        ~Entry(){}
    };
    
    typedef vector<forward_list<Entry>> bucket_t;
    class iterator{
        public :
        
        bucket_t & tab_buck;
        vector<forward_list<Entry>>::iterator current_bucket;                                                   //current bucket case
        forward_list<Entry>::iterator current_list;            //iterator of forward_list
        
        iterator(bucket_t & tab,vector<forward_list<Entry>>::iterator buck ,forward_list<Entry>::iterator c) : tab_buck(tab),current_bucket(buck),current_list(c){}
        
        iterator & operator++(){
            
            ++current_list;
            if(current_list == (*current_bucket).end()){
                ++current_bucket;
                auto & i = current_bucket;
                for(;i!=tab_buck.end();++i){
                    if(i->empty()){
                        continue;
                    }
                    current_list = i->begin();
                    break;
                }
            }
            return *this;
        }
        
        
        bool operator!=(const iterator &other) {
            return ((current_bucket!=other.current_bucket)|| (current_list != other.current_list));
        }
        
        
        Entry & operator*(){
            return *current_list;
        }
        
        Entry * operator->(){
            return &(*current_list);
            
            
        }
        
    };
    
    bucket_t buckets;
    size_t nb_elem=0;
    
    HashMap(size_t s):buckets(s){}
    
    ~HashMap(){}
    
    const V* get(const K & key) const{
        
        size_t h = (hash<K>()(key))%(buckets.capacity());
        //forward_list<Entry>::iterator iter = buckets[h].begin();
        
        for(auto const &p : buckets[h]){                     //essaie avec for(auto const p = (buckets[h].begin());p!=buckets[h].end();++p)  //ne marche pas pourquoi???
            if((p.Key)==key){
                return (&(p.Value));
            }
        }
        return nullptr;                                     //On a pas trouve la cle dans la hashap
    }
    
    bool put (const K & key, const V & value){
        size_t h = (std::hash<K>()(key))%(buckets.capacity());
        forward_list<Entry>& iter = buckets[h];
        nb_elem++;                              //NB mot dans la table
        if(iter.empty()){                        //si case vide on incremente le nombre de case prise
           
        }
        for(auto  &p : iter){                    //p de type Entry<K,V>  => p est deja la tructure que contient la liste et c est sur la liste qu on itere
            if((p.Key)==key){                    //si on a trouve la que la cle existe deja dans la hashmap
                p.Value = value;
                return  true;
            }
        }
        iter.emplace_front(key,value);           //si liste non vide sur h
        return false;
    }
    
    
    size_t size(){
        return nb_elem;
    }
    
    void grow(){                                     //Complexite lineaire en O(n+ buckets.capacity ) n = nombre de mot
        size_t new_size = buckets.capacity()*2;
        vector <forward_list<Entry>> temp (new_size);                        //initialise un vecteur de taille *2 de la taille precedente
        size_t h = 0;
        
        
        for(int i = 0; i<buckets.capacity();i++){         //Dans la boucle for on itere sur les n elements
            forward_list<Entry>& iter = buckets [i];
            if(iter.empty()){
                continue;
            }
            for(auto const & p : iter){
                h = (std::hash<K>()(p.Key))%(new_size);
                temp[h].emplace_front (p.Key,p.Value);        //O(1)
            }
            
            
        }
        buckets = temp;                              // complexite de new_size      complexite en buckets.capacity
    }
    
    void ensure_capacity(){
        int per = (nb_elem*100)/buckets.capacity();
        if (per > 80){
            grow();
        }
        
    }
    
    
    iterator begin(){
        auto i = buckets.begin();
        for(;i!=buckets.end();++i){
            if((*i).empty()){
                continue;
            }
            break;
        }
        
        if(i==buckets.end()){           //si on a pas trouve d'element
            return iterator(buckets,buckets.end(),buckets.front().end());
        }
        cout<<"out of begin"<<endl;
        return iterator (buckets,i,i->begin());
    }
    
    
    
    iterator end(){
        return iterator(buckets,buckets.end(),buckets.back().end());
    }
    
   
    
};



#endif /* hashtab_hpp */

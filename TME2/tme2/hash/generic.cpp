//
//  generic.cpp
//  
//
//  Created by Harena Rakotondratsima on 06/10/2023.
//

#include "generic.hpp"
template <typename iterator>

size_t count (iterator begin,iterator end){
    size_t c=0;
    for(auto it = begin; it !=end; it++){
        c++;
    }
    return c;
}

template <typename iterator,typename T>
size_t count_if_equal (iterator begin, iterator end, const T & val){
    
    size_t c=0;
    for(auto it = begin; it !=end; it++){
        if(*it==val){
            c++;
        }
    }
    return c;
}




//
//  generic.hpp
//  
//
//  Created by Harena Rakotondratsima on 06/10/2023.
//

#ifndef generic_hpp
#define generic_hpp

#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <utility>

template <typename iterator>
size_t count (iterator begin,iterator end);
template <typename iterator,typename T>
size_t count_if_equal (iterator begin, iterator end, const T & val);
#endif /* generic_hpp */

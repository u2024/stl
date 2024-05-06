#include <iostream>
#include <forward_list>
#include <deque>
#include "sort.hpp"

std::deque<std::string> lengthSort(std::forward_list<std::string> &list)
{
    std::deque<std::string> deque;
    list.sort();
    for(auto el : list) {
        deque.push_back(el);
    }
    for(int i = 1; i < deque.size(); ++i) {
        for(int k = i; k > 0; --k) {
            if(deque[k].size() < deque[k-1].size()) {
                std::swap(deque[k], deque[k-1]);
            }
        }
    }
    return deque;    
}

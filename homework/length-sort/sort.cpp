#include <iostream>
#include <forward_list>
#include <deque>
#include "sort.hpp"

auto lengthSort(std::forward_list<std::string> &list)
{
    std::deque<std::string> deque;
    list.sort();
    for(auto el : list)
    {
        deque.push_back(el);
    }
    for(int i = 0; i < deque.size(); ++i)
    {
        auto x = deque[i].size();
        for(int k = 0; k < deque.size(); ++k)
        {
            auto y = deque[k].size();
            if(x < y)
            {
                std::swap(deque[i], deque[k]);
            }
        }
    }
    return deque;    
}

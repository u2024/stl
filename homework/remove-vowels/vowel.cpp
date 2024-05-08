#include <string>
#include <vector>
#include <iostream>
#include <cctype>

void removeVowels(std::vector<std::string> &vec)
{
    for(auto &i : vec)
    {
        auto k = i.end();
        while (k != i.begin() - 1)
        {
            if(std::tolower(*k) == 'a' || std::tolower(*k) == 'e' || std::tolower(*k) == 'i' || std::tolower(*k) == 'o' || std::tolower(*k) == 'u' || std::tolower(*k) == 'y')
            {
                i.erase(k);
            }
            --k;
        }
    }
}

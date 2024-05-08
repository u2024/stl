#include <string>
#include <vector>
#include <iostream>

void removeVowels(std::vector<std::string> &vec)
{
    for(auto &i : vec)
    {
        auto k = i.end();
        while (k != i.begin() - 1)
        {
            if(*k == 'a' || *k == 'e' || *k == 'i' || *k == 'o' || *k == 'u' || *k == 'y')
            {
                i.erase(k);
            }
            --k;
        }
    }
}

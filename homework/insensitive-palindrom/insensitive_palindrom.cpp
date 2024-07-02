#include <algorithm>
#include <string>

bool is_palindrome(std::string str)
{
    bool b = true;
    for(int i = 0; i < str.size() && b; ++i)
    {
        for(int k = str.size() - 1; k > -1 && b; --k)
        {
            while(!isalnum(str[i]))
            {
                ++i;
            }
            while(!isalnum(str[k])
            {
                --k;
            }
            if(toupper(str[k]) == toupper(str[i]))
            {
                ++i;
                continue;
            }
            else b = false;
        }
    }
    return b;
}

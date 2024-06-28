#include <vector>
#include <utility>
#include <array>
#include <cstdint>
#include <cstddef>

constexpr size_t width = 32;
constexpr size_t height = 32;

std::vector<std::pair<uint8_t, uint8_t>> compressGrayscale(std::array<std::array<uint8_t, width>, height>& array)
{
    std::vector<std::pair<uint8_t, uint8_t>> vec;
    uint8_t count = 0, value1 = array[0][0];
    for(auto k = 0; k < array.size(); ++k)
    {
        for(auto i = 0; i < array[k].size(); ++i)
        {
            if(array[k][i] != value1 && count != 0)
            {
                vec.push_back(std::make_pair(value1, count));
                count = 0;
                value1 = array[k][i];
                ++count;
            }
            else ++count;
        }
        if(count != 0)
        {
            vec.push_back(std::make_pair(value1, count));
            count = 0;
            if(k + 1 != array.size())
                value1 = array[k + 1][0];
        }
    }
    return vec;
}

std::array<std::array<uint8_t, width>, height> decompressGrayscale(std::vector<std::pair<uint8_t, uint8_t>> &vec)
{
    std::array<std::array<uint8_t, width>, height> array;
    int l = 0, m = 0;
    for(auto i = 0; i < array.size(); ++i)
    {
        for(auto k = 0; k < array[i].size(); ++k)
        {
            if(vec[l].second != m)
            {
                array[i][k] = vec[l].first;
                ++m;
            }
            else 
            {
                while(vec[l].second == m || vec[l].second == 0)
                {
                    ++l;
                    m = 0;
                }
                array[i][k] = vec[l].first;
                ++m;
            }
        }
    }
    return array;
}

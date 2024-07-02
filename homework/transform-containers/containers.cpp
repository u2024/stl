#include <list>
#include <map>
#include <string>
#include <deque>
#include <algorithm>

std::map<int, std::string> removeDuplicateAndTranformToMap(std::list<std::string> &list, std::deque<int> &deq)
{
    std::map<int, std::string> map;
    list.sort();
    list.erase(std::unique(begin(list), end(list)), end(list));
    std::sort(begin(deq), end(deq));
    deq.erase(std::unique(begin(deq), end(deq)), end(deq));
    std::transform(begin(deq), end(deq), begin(list), begin(deq), [&map](auto &x, auto &y){ map[x] = y; return 0; });
    return map;
}

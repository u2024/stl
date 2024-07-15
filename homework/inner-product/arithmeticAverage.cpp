#include <vector>
#include <cmath>
#include <numeric>
#include <functional>

double ArithmeticAverage(std::vector<int> &v1, std::vector<int> &v2)
{
    double av = 0;
    av = std::inner_product(v1.begin(), v1.end(), v2.begin(), 0, std::plus<double>(), std::plus<double>());
    return av / (v1.size() + v2.size());
}

double Distance(std::vector<int> &v1, std::vector<int> &v2)
{
    double dist = 0;
    dist = std::inner_product(v1.begin(), v1.end(), v2.begin(), 0, std::plus<double>(), [](auto & x, auto & y){ return std::pow(x - y, 2); });
    return sqrt(dist);
}

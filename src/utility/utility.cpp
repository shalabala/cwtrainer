#include "utility.h"
#include <vector>

namespace cw_utility
{
    unsigned int upperPowerOfTwo(unsigned int v)
    {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v++;
        return v;
    }

    // template <typename T>
    // std::size_t ElementwiseHasher::operator()(const std::vector<T> &s) const noexcept
    // {
    //     std::size_t hash = 0;
    //     std::size_t p = s.size() * 3;
    //     std::hash<T> hasher;
    //     for (auto &&a : s)
    //     {
    //         hash = (hash + hasher(a)) * p;
    //     }
    //     return hash;
    // }
}
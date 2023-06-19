#include "utility.h"
#include<vector>

namespace cwUtility
{

    std::size_t ElementwiseHasher<T>::operator()(const std::vector<T> &s) const noexcept
    {
        std::size_t hash = 0;
        std::size_t p = 5;
        for (auto &&a : s)
        {
            hash = (hash + a) * p;
            p <<= 1;
        }
        return hash;
    }

}
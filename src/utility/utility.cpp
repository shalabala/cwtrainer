#include "utility.h"
#include <vector>
#include <cstdint>
#include <chrono>

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

    int64_t getCurrentTimeInMillis()
    {
        using namespace std::chrono;
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }
    
    int64_t getElapsedMillisecondsSince(int64_t timestamp)
    {
        return getCurrentTimeInMillis() - timestamp;
    }
}
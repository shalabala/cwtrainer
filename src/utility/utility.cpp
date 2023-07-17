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
    char preprocessAscii(char c)
    {
        if(c>= '0' && c <= '9'){
            return c;
        }
        if(c>= 'a' && c<='z'){
            return c;
        }
        if(c>= 'A' && c<= 'Z'){
            return c+('a'-'A');
        }
        throw std::invalid_argument("Only valid characters [a-zA-Z0-9] can be converted to morse");
    }
    bool tryPreprocessAscii(char c, char &res)
    {
        if(c>= '0' && c <= '9'){
            res = c;
            return true;
        }
        if(c>= 'a' && c<='z'){
            res= c;
            return true;
        }
        if(c>= 'A' && c<= 'Z'){
            res= c+('a'-'A');
            return true;
        }
        return false;
    }
}
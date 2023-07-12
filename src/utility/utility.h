#ifndef CWTRAINER_UTILITY_H
#define CWTRAINER_UTILITY_H
#include <unordered_map>
#include <vector>
#include <iostream>
#include <cstdint>
namespace cw_utility
{

    /**For the given number returns the next 2-power in constant time
     *
     */
    unsigned int upperPowerOfTwo(unsigned int v);

    /** Gets the current time in milliseconds since epoch
     *
     */
    int64_t getCurrentTimeInMillis();

    /** Time since the given timestamp
     *
     */
    int64_t getElapsedMillisecondsSince(int64_t timestamp);

} // namespace cwUtility

#endif
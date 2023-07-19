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

    /**
     * Empties the container
    */
    template<typename T>
    inline void clear(T &t){
        T().swap(t);
    }

    /**
     * This method only accepts [a-zA-Z0-9] characters, with other inputs it throws an exception.
     * All uppercase characters will be converted to lowercase in the return argument. Other valid characters
     * will simply be returned with no change
    */
    char preprocessAscii(char c);

    /**
     * Does the same as its one parameter counterpart, except that this one does not throw an exception,
     * instead returning a bool value wether the character was accepted or not
    */
    bool tryPreprocessAscii(char c, char &res);

    /** Is the character valid, morse convertible ascii char
     * 
    */
    bool isValidAscii(char c);

} // namespace cwUtility

#endif
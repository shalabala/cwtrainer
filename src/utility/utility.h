#ifndef UTILITY_H
#define UTILITY_H
namespace cwUtility
{

/**For the given number returns the next 2-power in constant time
 * 
*/
unsigned int upper_power_of_two(unsigned int v)
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

/**Elementwise hashing for vectors*/
template<typename T>
struct ElementwiseHasher{

    /**create hash*/
    std::size_t operator()(const std::vector<T>& s) const noexcept;
};
} // namespace cwUtility

#endif
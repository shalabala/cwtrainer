#include "morse-types.h"
#include <iostream>
namespace morse
{
    std::size_t MorseStringHasher::operator()(const MorseString &s) const noexcept
    {
            std::size_t hash = 0;
            std::size_t p = 7;
            std::hash<MorseSymbol> hasher;
            for (auto &&a : s)
            {
                hash = (hash + hasher(a)) * p;
            }
            return hash;
    }
}
std::ostream &operator<<(std::ostream &outStream, const morse::MorseString &mstring)
{
    for (auto &&i : mstring)
    {
        switch (i)
        {
        case morse::dot:
            outStream << ".";
            break;
        case morse::dash:
            outStream << "-";
            break;
        case morse::letterEnd:
            break;
        case morse::wordEnd:
            outStream << " ";
            break;
        default:
            break;
        }
    }
    return outStream;
}

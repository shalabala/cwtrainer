#include "morse-types.h"
#include <iostream>
namespace morse
{
    std::size_t MorseLetterHasher::operator()(const MorseStringIterator &s) const noexcept
    {
        std::size_t hash = 0;
        std::size_t p = 47;
        std::hash<MorseSymbol> hasher;
        MorseStringIterator element = s;
        for (; isBeep(*element); ++element)
        {
            hash = (hash + hasher(*element)) * p;
        }
        return hash;
    }

    bool MorseLetterEquals::operator()(const MorseStringIterator &lhs, const MorseStringIterator &rhs) const noexcept
    {
        MorseStringIterator rhsElement = rhs;
        MorseStringIterator lhsElement = lhs;
        for (; isBeep(*rhsElement) && isBeep(*lhsElement); ++rhsElement, ++lhsElement)
        {
            if (*rhsElement != *lhsElement)
            {
                return false;
            }
        }
        return true;
    }

    int getLengthInDots(const MorseString &str)
    {
        int total = 0;
        for (auto &&i : str)
        {
            switch (i)
            {
            case dot:
                total += 1;
                break;
            case dash:
                total += 3;
                break;
            case letterEnd:
                total += 3;
                break;
            case wordEnd:
                // word end characters are always followed by and preceeded by a letter end character.
                // its value should be 7, so the 3+1+3 gives exactly that result
                total += 1;
                break;
            default:
                break;
            }
        }
        return total;
    }

}
std::ostream &operator<<(std::ostream &outStream, const morse::MorseStringIterator &iterator)
{
    for (morse::MorseStringIterator modifiableIterator = iterator; *modifiableIterator != morse::textEnd; ++modifiableIterator)
        outStream << *modifiableIterator;
    return outStream;
}
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
            if(*rhsElement != *lhsElement){
                return false;
            }
        }
        return true;
    }

}
std::ostream &operator<<(std::ostream &outStream, const morse::MorseStringIterator &iterator)
{
    for(morse::MorseStringIterator modifiableIterator = iterator; *modifiableIterator != morse::textEnd; ++modifiableIterator)
    outStream << *modifiableIterator;
    return outStream;
}
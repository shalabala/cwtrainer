#include "morse-types.h"
#include <iostream>
namespace morse
{
    std::size_t MorseStringIteratorHasher::operator()(const MorseStringIterator &s) const noexcept
    {
        std::size_t hash = 0;
        std::size_t p = 7;
        std::hash<MorseSymbol> hasher;
        for (MorseStringIterator element = s; *element >= dot; element++)
        {
            hash = (hash + hasher(*element)) * p;
        }
        return hash;
    }

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

    std::string convertMorseSymbolToString(MorseSymbol sym)
    {
        switch (sym)
        {
        case morse::dot:
            return ".";
            break;
        case morse::dash:
            return "-";
            break;
        case morse::letterEnd:
            return " ";
            break;
        case morse::wordEnd:
            return "   ";
            break;
        default:
            return "";
            break;
        }
    }

    std::string convertMorseStringToString(const MorseStringIterator &str)
    {
        std::string s;
        for (MorseStringIterator iterator = str; *iterator != textEnd; ++iterator)
        {
            std::string symbolTranslation = convertMorseSymbolToString(*iterator);
            s.append(symbolTranslation);
        }
        return std::move(s);
    }

    std::string convertMorseStringToString(const MorseString &str)
    {
        return convertMorseStringToString(str.begin());
    }
}
std::ostream &operator<<(std::ostream &outStream, const morse::MorseString &mstring)
{
    outStream << morse::convertMorseStringToString(mstring);
    return outStream;
}

std::ostream &operator<<(std::ostream &outStream, const morse::MorseStringIterator &iterator)
{
    outStream << morse::convertMorseStringToString(iterator);
    return outStream;
}

#include "morse-translator.h"
#include <string>

namespace morse
{
    MorseTranslate::MorseTranslate(const MorseAlphabet &morseAlphabet) : alphabet(morseAlphabet)
    {
    }

    std::string MorseTranslate::translate(const MorseString &symbols) const
    {
        return translate(symbols.begin());
    }

    std::string MorseTranslate::translate(const MorseStringIterator &symbols) const
    {
        std::string translatedString("");
        MorseStringIterator iterator = symbols;
        while (*iterator >= dot)
        {
            char letter = alphabet.translateLetter(iterator);
            translatedString += letter;
            while (*iterator != letterEnd)
            {
                ++iterator;
            }
            ++iterator;
        }
        return std::move(translatedString);
    }

    MorseString MorseTranslate::translate(const std::string text) const
    {
        MorseString s;
        for (auto &&i : text)
        {
            if (i == ' ')
            {
                s.push_back(wordEnd);
            }
            else
            {
                MorseStringIterator iterator = alphabet.translateLetter(i);
                for (; *iterator != textEnd; ++iterator){
                    s.push_back(*iterator);
                }
            }
        }
        return std::move(s);
    }
}

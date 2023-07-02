#include "morse-translator.h"
#include "morse-types.h"
#include <string>

namespace morse
{
    MorseTranslate::MorseTranslate(const MorseAlphabet &morseAlphabet) : alphabet(morseAlphabet)
    {
    }

    std::string MorseTranslate::translateMorseToText(const MorseString &symbols) const
    {
        return translateMorseToText(symbols.begin());
    }

    std::string MorseTranslate::translateMorseToText(const MorseStringIterator &symbols) const
    {
        std::string translatedString("");
        MorseStringIterator iterator = symbols;
        while (*iterator != textEnd)
        {
            while (isBeep(*iterator))
            {
                char letter = alphabet.translateLetter(iterator);
                translatedString += letter;
                while (isBeep(*iterator))
                {
                    ++iterator;
                }
            }
            if (*iterator == wordEnd)
            {
                translatedString += ' ';
                ++iterator;
            }
            else if (*iterator == letterEnd)
            {
                ++iterator;
            }
        }
        return std::move(translatedString);
    }

    MorseString MorseTranslate::translateTextToMorse(const std::string text) const
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
                for (; *iterator != textEnd; ++iterator)
                {
                    s.push_back(*iterator);
                }
                s.push_back(letterEnd);
            }
        }
        return std::move(s);
    }
}

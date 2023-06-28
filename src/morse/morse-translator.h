#ifndef MORSE_TRANSLATOR_H
#define MORSE_TRANSLATOR_H
#include <string>
#include "morse-types.h"
#include "morse-alphabet.h"
namespace morse
{
    class MorseTranslate
    {
    public:
        MorseTranslate(const MorseAlphabet &morseAlphabet);
        std::string translateMorseToText(const MorseString &symbols) const;
        std::string translateMorseToText(const MorseStringIterator &symbols) const;
        MorseString translateTextToMorse(const std::string text) const;

    private:
        MorseAlphabet alphabet;
    };
}
#endif

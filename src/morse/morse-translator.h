#ifndef CWTRAINER_MORSE_TRANSLATOR_H
#define CWTRAINER_MORSE_TRANSLATOR_H
#include "morse-types.h"
#include "morse-alphabet.h"
#include <string>
namespace morse
{
    class MorseTranslate
    {
    public:
        explicit MorseTranslate(const MorseAlphabet &morseAlphabet);
        std::string translateMorseToText(const MorseString &symbols) const;
        std::string translateMorseToText(const MorseStringIterator &symbols) const;
        MorseString translateTextToMorse(const std::string text) const;

    private:
        MorseAlphabet alphabet;
    };
}
#endif

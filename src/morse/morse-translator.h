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
        std::string translate(const MorseString &symbols) const;
        std::string translate(const MorseStringIterator &symbols) const;
        MorseString translate(const std::string text) const;

    private:
        MorseAlphabet alphabet;
    };
}
#endif

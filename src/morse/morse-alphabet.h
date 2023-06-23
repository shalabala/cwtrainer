#ifndef MORSE_ALPHABET_H
#define MORSE_ALPHABET_H
#include <vector>
#include <unordered_map>
#include <string>
#include "morse-types.h"
#include "../utility/utility.h"
namespace morse
{
    class MorseAlphabet
    {
    public:
        MorseAlphabet();
        /**Translates single character to equivalent morse string*/
        const MorseStringIterator &translateLetter(char c) const;
        /**Translates a morse letter to the equivalent character. It is presumed that the string contains only a single letter*/
        char translateLetter(const MorseString &letter) const;
        /**Translates the next morse letter in the string to the equivalent character.
         * If the iterated container does not contain an ending character (letterEnd or wordEnd) the call might result in a SIGSEGV error*/
        char translateLetter(const MorseStringIterator &iterator) const;

    private:
        std::unordered_map<char, MorseStringIterator> charToMorse;
        std::unordered_map<MorseStringIterator, char, MorseStringIteratorHasher> morseToChar;
    };
    
}
#endif
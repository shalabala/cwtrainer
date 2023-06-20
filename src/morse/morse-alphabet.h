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
        const MorseString &translateLetter(char c) const;
        char translateLetter(const MorseString &letter) const;

    private:
        std::unordered_map<char, MorseString> charToMorse;
        std::unordered_map<MorseString, char, MorseStringHasher> morseToChar;
    };
}
#endif
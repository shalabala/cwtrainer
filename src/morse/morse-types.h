#ifndef MORSE_TYPES_H
#define MORSE_TYPES_H
#include <vector>
#include <iostream>
namespace morse
{
    /**Simple morse symbols for dots, dashes and pauses
     *
     */
    enum MorseSymbol
    {
        //     /**End of morse text
        //      *
        //      */
        //     letterEnd = 0,
        /**Single unit morse sign
         *
         */
        dot = 1,
        /**Morse sign that is equivalent in length with 3 dots
         *
         */
        dash,
        /**pause between letters, equivalent silence of 3 dots
         *
         */
        letterEnd,
        /**pause between words, equivalent silence of 7 dots
         *
         */
        wordEnd,

    };

    /**type that is used to iterate over a
     *
     */
    typedef std::vector<MorseSymbol>::iterator MorseStringIterator;

    /**string of morse symbols
     *
     */
    typedef std::vector<MorseSymbol> MorseString;

    const MorseString MORSE_LETTER_A = {dot, dash, letterEnd};
    const MorseString MORSE_LETTER_B = {dash, dot, dot, dot, letterEnd};
    const MorseString MORSE_LETTER_C = {dash, dot, dash, dot, letterEnd};
    const MorseString MORSE_LETTER_D = {dash, dot, dot, letterEnd};
    const MorseString MORSE_LETTER_E = {dot, letterEnd};
    const MorseString MORSE_LETTER_F = {dot, dot, dash, dot, letterEnd};
    const MorseString MORSE_LETTER_G = {dash, dash, dot, letterEnd};
    const MorseString MORSE_LETTER_H = {dot, dot, dot, dot, letterEnd};
    const MorseString MORSE_LETTER_I = {dot, dot, letterEnd};
    const MorseString MORSE_LETTER_J = {dot, dash, dash, dash, letterEnd};
    const MorseString MORSE_LETTER_K = {dash, dot, dash, letterEnd};
    const MorseString MORSE_LETTER_L = {dot, dash, dot, dot, letterEnd};
    const MorseString MORSE_LETTER_M = {dash, dash, letterEnd};
    const MorseString MORSE_LETTER_N = {dash, dot, letterEnd};
    const MorseString MORSE_LETTER_O = {dash, dash, dash, letterEnd};
    const MorseString MORSE_LETTER_P = {dot, dash, dash, dot, letterEnd};
    const MorseString MORSE_LETTER_Q = {dash, dash, dot, dash, letterEnd};
    const MorseString MORSE_LETTER_R = {dot, dash, dot, letterEnd};
    const MorseString MORSE_LETTER_S = {dot, dot, dot, letterEnd};
    const MorseString MORSE_LETTER_T = {dash, letterEnd};
    const MorseString MORSE_LETTER_U = {dot, dot, dash, letterEnd};
    const MorseString MORSE_LETTER_V = {dot, dot, dot, dash, letterEnd};
    const MorseString MORSE_LETTER_W = {dot, dash, dash, letterEnd};
    const MorseString MORSE_LETTER_X = {dash, dot, dot, dash, letterEnd};
    const MorseString MORSE_LETTER_Y = {dash, dot, dash, dash, letterEnd};
    const MorseString MORSE_LETTER_Z = {dash, dash, dot, dot, letterEnd};
    const MorseString MORSE_LETTER_0 = {dash, dash, dash, dash, dash, letterEnd};
    const MorseString MORSE_LETTER_1 = {dot, dash, dash, dash, dash, letterEnd};
    const MorseString MORSE_LETTER_2 = {dot, dot, dash, dash, dash, letterEnd};
    const MorseString MORSE_LETTER_3 = {dot, dot, dot, dash, dash, letterEnd};
    const MorseString MORSE_LETTER_4 = {dot, dot, dot, dot, dash, letterEnd};
    const MorseString MORSE_LETTER_5 = {dot, dot, dot, dot, dot, letterEnd};
    const MorseString MORSE_LETTER_6 = {dash, dot, dot, dot, dot, letterEnd};
    const MorseString MORSE_LETTER_7 = {dash, dash, dot, dot, dot, letterEnd};
    const MorseString MORSE_LETTER_8 = {dash, dash, dash, dot, dot, letterEnd};
    const MorseString MORSE_LETTER_9 = {dash, dash, dash, dash, dot, letterEnd};

    /**Hasher for morse strings*/
    struct MorseStringHasher
    {
        /**create hash*/
        std::size_t operator()(const MorseString &s) const noexcept;
    };
} // namespace morse

std::ostream &operator<<(std::ostream& outStream, const morse::MorseString &mstring);

#endif
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
        /**End of morse text
         * Terminal symbol in all contexts.
         */
        textEnd,

        /**pause between words, equivalent silence of 7 dots
         * Terminal symbol in some contexts
         */

        wordEnd,

        /**pause between letters, equivalent silence of 3 dots
         * Terminal symbol in some contexts.
         */
        letterEnd,

        /**Single unit morse sign
         * In comparisons, all symbols with value >=dot are non terminal symbols,
         * all symbols with <dot are terminal symbols
         */
        dot,

        /**Morse sign that is equivalent in length of 3 dots
         */
        dash,
    };

    /**type that is used to iterate over a MorseString
     *
     */
    typedef std::vector<MorseSymbol>::const_iterator MorseStringIterator;

    /**string of morse symbols
     *
     */
    typedef std::vector<MorseSymbol> MorseString;

    const MorseString morseLetterA = {dot, dash, letterEnd, textEnd};
    const MorseString morseLetterB = {dash, dot, dot, dot, letterEnd, textEnd};
    const MorseString morseLetterC = {dash, dot, dash, dot, letterEnd, textEnd};
    const MorseString morseLetterD = {dash, dot, dot, letterEnd, textEnd};
    const MorseString morseLetterE = {dot, letterEnd, textEnd};
    const MorseString morseLetterF = {dot, dot, dash, dot, letterEnd, textEnd};
    const MorseString morseLetterG = {dash, dash, dot, letterEnd, textEnd};
    const MorseString morseLetterH = {dot, dot, dot, dot, letterEnd, textEnd};
    const MorseString morseLetterI = {dot, dot, letterEnd, textEnd};
    const MorseString morseLetterJ = {dot, dash, dash, dash, letterEnd, textEnd};
    const MorseString morseLetterK = {dash, dot, dash, letterEnd, textEnd};
    const MorseString morseLetterL = {dot, dash, dot, dot, letterEnd, textEnd};
    const MorseString morseLetterM = {dash, dash, letterEnd, textEnd};
    const MorseString morseLetterN = {dash, dot, letterEnd, textEnd};
    const MorseString morseLetterO = {dash, dash, dash, letterEnd, textEnd};
    const MorseString morseLetterP = {dot, dash, dash, dot, letterEnd, textEnd};
    const MorseString morseLetterQ = {dash, dash, dot, dash, letterEnd, textEnd};
    const MorseString morseLetterR = {dot, dash, dot, letterEnd, textEnd};
    const MorseString morseLetterS = {dot, dot, dot, letterEnd, textEnd};
    const MorseString morseLetterT = {dash, letterEnd, textEnd};
    const MorseString morseLetterU = {dot, dot, dash, letterEnd, textEnd};
    const MorseString morseLetterV = {dot, dot, dot, dash, letterEnd, textEnd};
    const MorseString morseLetterW = {dot, dash, dash, letterEnd, textEnd};
    const MorseString morseLetterX = {dash, dot, dot, dash, letterEnd, textEnd};
    const MorseString morseLetterY = {dash, dot, dash, dash, letterEnd, textEnd};
    const MorseString morseLetterZ = {dash, dash, dot, dot, letterEnd, textEnd};
    const MorseString morseLetter0 = {dash, dash, dash, dash, dash, letterEnd, textEnd};
    const MorseString morseLetter1 = {dot, dash, dash, dash, dash, letterEnd, textEnd};
    const MorseString morseLetter2 = {dot, dot, dash, dash, dash, letterEnd, textEnd};
    const MorseString morseLetter3 = {dot, dot, dot, dash, dash, letterEnd, textEnd};
    const MorseString morseLetter4 = {dot, dot, dot, dot, dash, letterEnd, textEnd};
    const MorseString morseLetter5 = {dot, dot, dot, dot, dot, letterEnd, textEnd};
    const MorseString morseLetter6 = {dash, dot, dot, dot, dot, letterEnd, textEnd};
    const MorseString morseLetter7 = {dash, dash, dot, dot, dot, letterEnd, textEnd};
    const MorseString morseLetter8 = {dash, dash, dash, dot, dot, letterEnd, textEnd};
    const MorseString morseLetter9 = {dash, dash, dash, dash, dot, letterEnd, textEnd};

    /**Size of longest morse letters, without letter separator*/
    const int longestLetterLength = 5;

    /**Hasher for morse strings*/
    struct MorseStringHasher
    {
        /**create hash*/
        std::size_t operator()(const MorseString &s) const noexcept;
    };

    struct MorseStringIteratorHasher
    {
        /**create hash*/
        std::size_t operator()(const MorseStringIterator &s) const noexcept;
    };

    std::string convertMorseSymbolToString(MorseSymbol sym);

    std::string convertMorseStringToString(const MorseStringIterator &str);

    std::string convertMorseStringToString(const MorseString &str);
} // namespace morse

std::ostream &operator<<(std::ostream &outStream, const morse::MorseString &mstring);

std::ostream &operator<<(std::ostream &outStream, const morse::MorseStringIterator &mstring);

#endif
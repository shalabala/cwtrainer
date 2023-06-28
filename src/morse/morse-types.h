#ifndef MORSE_TYPES_H
#define MORSE_TYPES_H
#include <vector>
#include <iostream>
#include <string>
namespace morse
{
     /**Simple morse symbols for dots, dashes and pauses
     *
     */
    typedef char MorseSymbol;

    /**type that is used to iterate over a MorseString
     *
     */
    typedef std::string::const_iterator MorseStringIterator;

    /**string of morse symbols
     *
     */
    typedef std::string MorseString;

    /**End of morse text
     * 
    */
    const MorseSymbol textEnd = '\0';

    /**pause between words, equivalent silence of 7 dots
     * Terminal symbol in some contexts
     * char value 47
     */
    const MorseSymbol wordEnd = '/';

    /**pause between letters, equivalent silence of 3 dots
     * Terminal symbol in some contexts.
     * char value 32
     */
    const MorseSymbol letterEnd = ' ';

    /**Single unit morse sign
     * In comparisons, all symbols with value >=dot are non terminal symbols,
     * all symbols with <dot are terminal symbols
     * char value 46
     */
    const MorseSymbol dot = '.';

    /**Morse sign that is equivalent in length of 3 dots
     * char value 45
     */
    const MorseSymbol dash = '-';

    const MorseString morseLetterA = ".-";
    const MorseString morseLetterB = "-...";
    const MorseString morseLetterC = "-.-.";
    const MorseString morseLetterD = "-..";
    const MorseString morseLetterE = ".";
    const MorseString morseLetterF = "..-.";
    const MorseString morseLetterG = "--.";
    const MorseString morseLetterH = "....";
    const MorseString morseLetterI = "..";
    const MorseString morseLetterJ = ".---";
    const MorseString morseLetterK = "-.-";
    const MorseString morseLetterL = ".-..";
    const MorseString morseLetterM = "--";
    const MorseString morseLetterN = "-.";
    const MorseString morseLetterO = "---";
    const MorseString morseLetterP = ".--.";
    const MorseString morseLetterQ = "--.-";
    const MorseString morseLetterR = ".-.";
    const MorseString morseLetterS = "...";
    const MorseString morseLetterT = "-";
    const MorseString morseLetterU = "..-";
    const MorseString morseLetterV = "...-";
    const MorseString morseLetterW = ".--";
    const MorseString morseLetterX = "-..-";
    const MorseString morseLetterY = "-.--";
    const MorseString morseLetterZ = "--..";
    const MorseString morseLetter0 = "-----";
    const MorseString morseLetter1 = ".----";
    const MorseString morseLetter2 = "..---";
    const MorseString morseLetter3 = "...--";
    const MorseString morseLetter4 = "....-";
    const MorseString morseLetter5 = ".....";
    const MorseString morseLetter6 = "-....";
    const MorseString morseLetter7 = "--...";
    const MorseString morseLetter8 = "---..";
    const MorseString morseLetter9 = "----.";

    /** Is the given morse symbol a beep (dot or dash) symbol*/
    inline bool isBeep(MorseSymbol s){
        return s == dot || s == dash;
    };

    /**Size of longest morse letters, without letter separator*/
    const int longestLetterLength = 5;

    struct MorseLetterHasher
    {
        /**create hash*/
        std::size_t operator()(const MorseStringIterator &s) const noexcept;
    };

    struct MorseLetterEquals
    {
        /**check if equal*/
        bool operator()(const MorseStringIterator &lhs, const MorseStringIterator &rhs) const noexcept;
    };
} 
std::ostream &operator<<(std::ostream &outStream, const morse::MorseStringIterator &iterator);
#endif
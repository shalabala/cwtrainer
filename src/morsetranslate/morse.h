#ifndef MORSE_H
#define MORSE_H
#include<vector>
#include<unordered_map>
#include<string>
namespace morse{
/**Simple morse symbols for dots, dashes and pauses
 *
 */
enum MorseSymbol
{
    /**Single unit morse sign
     * 
    */
    dot,
    /**Morse sign that is equivalent in length with 3 dots
     * 
    */
    dash,
    /**pause between letters, equivalent silence of 3 dots
     * 
    */
    letterPause,
    /**pause between letters, equivalent silence of 7 dots
     * 
    */
    wordPause
};

class MorseAlphabet{
    public:
        MorseAlphabet();
        std::vector<MorseSymbol> translateLetter(char c) const;
        char translateLetter(const std::vector<MorseSymbol>& symbols) const;
    private:
        std::unordered_map <char, std::vector<MorseSymbol>> charToMorse;
        std::unordered_map <std::vector<MorseSymbol>, char> morseToChar;
};


class MorseTranslate{
    public:
        MorseTranslate(const MorseAlphabet& morseAlphabet);
        std::string translate(const std::vector<MorseSymbol>& symbols) const;
        std::vector<MorseSymbol> translate(const std::string text) const;
    private:
        MorseAlphabet alphabet;
};
}
#endif
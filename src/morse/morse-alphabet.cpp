#include "morse-alphabet.h"
#include "morse-types.h"
#include "../utility/utility.h"

#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
namespace morse
{
    /**Ascii letters A-Z
     */
    const int NUMBER_OF_LETTERS = 26;
    /**Numbers 0-9
     */
    const int NUMBER_OF_SPECIAL_CHARACTERS = 10;
    const int SYMBOL_COUNT = NUMBER_OF_LETTERS + NUMBER_OF_SPECIAL_CHARACTERS;

    morse::MorseAlphabet::MorseAlphabet() : charToMorse(cw_utility::upperPowerOfTwo(SYMBOL_COUNT)),
                                            morseToChar(cw_utility::upperPowerOfTwo(SYMBOL_COUNT))
    {
        charToMorse['a'] = morseLetterA.begin();
        charToMorse['b'] = morseLetterB.begin();
        charToMorse['c'] = morseLetterC.begin();
        charToMorse['d'] = morseLetterD.begin();
        charToMorse['e'] = morseLetterE.begin();
        charToMorse['f'] = morseLetterF.begin();
        charToMorse['g'] = morseLetterG.begin();
        charToMorse['h'] = morseLetterH.begin();
        charToMorse['i'] = morseLetterI.begin();
        charToMorse['j'] = morseLetterJ.begin();
        charToMorse['k'] = morseLetterK.begin();
        charToMorse['l'] = morseLetterL.begin();
        charToMorse['m'] = morseLetterM.begin();
        charToMorse['n'] = morseLetterN.begin();
        charToMorse['o'] = morseLetterO.begin();
        charToMorse['p'] = morseLetterP.begin();
        charToMorse['q'] = morseLetterQ.begin();
        charToMorse['r'] = morseLetterR.begin();
        charToMorse['s'] = morseLetterS.begin();
        charToMorse['t'] = morseLetterT.begin();
        charToMorse['u'] = morseLetterU.begin();
        charToMorse['v'] = morseLetterV.begin();
        charToMorse['w'] = morseLetterW.begin();
        charToMorse['x'] = morseLetterX.begin();
        charToMorse['y'] = morseLetterY.begin();
        charToMorse['z'] = morseLetterZ.begin();
        charToMorse['0'] = morseLetter0.begin();
        charToMorse['1'] = morseLetter1.begin();
        charToMorse['2'] = morseLetter2.begin();
        charToMorse['3'] = morseLetter3.begin();
        charToMorse['4'] = morseLetter4.begin();
        charToMorse['5'] = morseLetter5.begin();
        charToMorse['6'] = morseLetter6.begin();
        charToMorse['7'] = morseLetter7.begin();
        charToMorse['8'] = morseLetter8.begin();
        charToMorse['9'] = morseLetter9.begin();
        
        // put the reverse into the other map
        for (auto &&i : charToMorse)
        {
            morseToChar[i.second] = i.first;
        }
    }

    char preprocessConvertedChar(char c){
        if(c>= '0' && c <= '9'){
            return c;
        }
        if(c>= 'a' && c<='z'){
            return c;
        }
        if(c>= 'A' && c<= 'Z'){
            return c+('a'-'A');
        }
        throw std::invalid_argument("Only valid characters [a-zA-Z0-9] can be converted to morse");
    }

    const MorseStringIterator& MorseAlphabet::translateLetter(char c) const
    {
        char toTranslate = preprocessConvertedChar(c);
        const MorseStringIterator& letter = charToMorse.at(toTranslate);
        return letter;
    }

    char MorseAlphabet::translateLetter(const MorseString &letter) const
    {   
        char translation=translateLetter(letter.begin());
        return translation;
    }
    
    char MorseAlphabet::translateLetter(const MorseStringIterator &letter) const
    {
       char translation = morseToChar.at(letter);
       return translation;
    }
}

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

    morse::MorseAlphabet::MorseAlphabet() : charToMorse(cwUtility::upper_power_of_two(SYMBOL_COUNT)),
                                            morseToChar(cwUtility::upper_power_of_two(SYMBOL_COUNT))
    {
        charToMorse['a'] = MORSE_LETTER_A;
        charToMorse['b'] = MORSE_LETTER_B;
        charToMorse['c'] = MORSE_LETTER_C;
        charToMorse['d'] = MORSE_LETTER_D;
        charToMorse['e'] = MORSE_LETTER_E;
        charToMorse['f'] = MORSE_LETTER_F;
        charToMorse['g'] = MORSE_LETTER_G;
        charToMorse['h'] = MORSE_LETTER_H;
        charToMorse['i'] = MORSE_LETTER_I;
        charToMorse['j'] = MORSE_LETTER_J;
        charToMorse['k'] = MORSE_LETTER_K;
        charToMorse['l'] = MORSE_LETTER_L;
        charToMorse['m'] = MORSE_LETTER_M;
        charToMorse['n'] = MORSE_LETTER_N;
        charToMorse['o'] = MORSE_LETTER_O;
        charToMorse['p'] = MORSE_LETTER_P;
        charToMorse['q'] = MORSE_LETTER_Q;
        charToMorse['r'] = MORSE_LETTER_R;
        charToMorse['s'] = MORSE_LETTER_S;
        charToMorse['t'] = MORSE_LETTER_T;
        charToMorse['u'] = MORSE_LETTER_U;
        charToMorse['v'] = MORSE_LETTER_V;
        charToMorse['w'] = MORSE_LETTER_W;
        charToMorse['x'] = MORSE_LETTER_X;
        charToMorse['y'] = MORSE_LETTER_Y;
        charToMorse['z'] = MORSE_LETTER_Z;
        charToMorse['0'] = MORSE_LETTER_0;
        charToMorse['1'] = MORSE_LETTER_1;
        charToMorse['2'] = MORSE_LETTER_2;
        charToMorse['3'] = MORSE_LETTER_3;
        charToMorse['4'] = MORSE_LETTER_4;
        charToMorse['5'] = MORSE_LETTER_5;
        charToMorse['6'] = MORSE_LETTER_6;
        charToMorse['7'] = MORSE_LETTER_7;
        charToMorse['8'] = MORSE_LETTER_8;
        charToMorse['9'] = MORSE_LETTER_9;
        
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

    const MorseString& MorseAlphabet::translateLetter(char c) const
    {
        char toTranslate = preprocessConvertedChar(c);
        const MorseString& letter = charToMorse.at(toTranslate);
        return letter;
    }
    char MorseAlphabet::translateLetter(const MorseString &letter) const
    {
       char translation = morseToChar.at(letter);
       return translation;
    }
}

#include "morse.h"
#include<vector>
#include<unordered_map>
#include<string>
#include "../utility/utility.h"
namespace morse{
/**Ascii letters A-Z
 */
const int NUMBER_OF_LETTERS=26;
/**Numbers 0-9
*/
const int NUMBER_OF_SPECIAL_CHARACTERS=10;

template<typename T>
struct MorseStringHasher{

    std::size_t operator()(const std::vector<T>& s) const noexcept{
        size_t hash=0;
        size_t p = 5;
        for (auto &&a : s)
        {   
            hash=(hash+a)*p;
            p<<=1;
            
        }
        return hash;
    }
};

morse::MorseAlphabet::MorseAlphabet(): charToMorse(cwUtility::upper_power_of_two(NUMBER_OF_LETTERS+NUMBER_OF_SPECIAL_CHARACTERS)),
morseToChar(cwUtility::upper_power_of_two(cwUtility::upper_power_of_two(NUMBER_OF_LETTERS+NUMBER_OF_SPECIAL_CHARACTERS), MorseStringHasher))
{
}

std::vector<MorseSymbol> morse::MorseAlphabet::translateLetter(char c) const
{
    auto s=charToMorse[c];
    return std::vector<MorseSymbol>();
}

char morse::MorseAlphabet::translateLetter(const std::vector<MorseSymbol> &symbols) const
{
    return ;
}
}

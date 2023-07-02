#include "SDL.h"
#include "SDL_audio.h"
#include "morse/morse-types.h"
#include "beeper.h"
#include "morse/morse-alphabet.h"
#include "morse/morse-translator.h"
#include <queue>
#include <iostream>
#include <cmath>
#include <memory>

const int FREQ = 800;
const int AMPLITUDE = 28000;

int main()
{
    std::unique_ptr<beeper::IBeeper> beeper = std::make_unique<beeper::Beeper>(FREQ, AMPLITUDE, 80);
    morse::MorseAlphabet alphabet;
    morse::MorseTranslate translator(alphabet);

    std::cout << "Geben Sie einen Text ein! ";
    std::string s;
    std::cin >> s;

    
    std::cout << std::endl;
}
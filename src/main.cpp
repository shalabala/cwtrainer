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

const int FREQ = 550;
const int AMPLITUDE = 28000;

int main()
{
    std::cout << "Please enter a text to be translated! ";
    std::string s;
    std::getline(std::cin, s);

    std::unique_ptr<beeper::IBeeper> beeper = std::make_unique<beeper::Beeper>(FREQ, AMPLITUDE, 60);
    morse::MorseAlphabet alphabet;
    morse::MorseTranslate translator(alphabet);

    morse::MorseString translation = translator.translateTextToMorse(s);

    std::cout << "The translation is: "<< translation << std::endl;

    beeper->schedule(translation);
    beeper->wait();
}


#ifndef CWTRAINER_BEEPER_TYPES_H
#define CWTRAINER_BEEPER_TYPES_H
namespace beeper
{
    struct Beep
    {
        Beep(int freq, int samplesLeft): freq(freq), samplesLeft(samplesLeft){}
        int freq;
        int samplesLeft;
    };
}
#endif
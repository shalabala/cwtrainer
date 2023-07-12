#ifndef CWTRAINER_CONFIGURATION_H
#define CWTRAINER_CONFIGURATION_H
namespace configuration
{
    class Configuration
    {
    public:
        int getDotLength();
        int getDashLength();
        int getWordEndLength();
        int getLetterEndLength();
        int getDashThresholdLength();
        int getBeeperFrequency();
        int getBeeperAmplitude();
        int getSingleKeyScanCode();
        int getDotKeyScanCode();
        int getDashKeyScanCode();
    };
}

#endif
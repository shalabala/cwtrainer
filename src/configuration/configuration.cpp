#include "configuration.h"

namespace configuration
{
    int Configuration::getDotLength()
    {
        return 150;
    }
    int Configuration::getDashLength()
    {
        return getDotLength() * 3;
    }

    int Configuration::getWordEndLength()
    {
        return getDotLength() * 7;
    }

    int Configuration::getLetterEndLength()
    {
        return getDotLength() * 3;
    }

    int Configuration::getDashThresholdLength()
    {
        return getDashLength() / 2;
    }
    int Configuration::getBeeperFrequency()
    {
        return 550;
    }
    int Configuration::getBeeperAmplitude()
    {
        return 28000;
    }
    int Configuration::getSingleKeyScanCode()
    {
        return 32;
    }
    int Configuration::getDotKeyScanCode()
    {
        return 70;
    }
    int Configuration::getDashKeyScanCode()
    {
        return 71;
    }
}
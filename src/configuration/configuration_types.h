#ifndef CWTRAINER_CONFIGURATION_TYPES
#define CWTRAINER_CONFIGURATION_TYPES

#include <string>

#define toStr(name) #name

namespace configuration
{
    enum Difficulty
    {
        easy,
        medium,
        hard
    };
    enum ConfigurationKey
    {
        dotLength = 0,
        dashLength,
        wordEndLength,
        letterEndLength,
        dashThresholdLength,
        defaultDifficulty,
        beeperFrequency,
        beeperAmplitude,
        singleKeyScanCode,
        dotKeyScanCode,
        dashKeyScanCode,
    };
    const std::string keyToString[] =
        {
            toStr(dotLength),
            toStr(dashLength),
            toStr(wordEndLength),
            toStr(letterEndLength),
            toStr(dashThresholdLength),
            toStr(defaultDifficulty),
            toStr(beeperFrequency),
            toStr(beeperAmplitude),
            toStr(singleKeyScanCode),
            toStr(dotKeyScanCode),
            toStr(dashKeyScanCode),
    };
}
#endif
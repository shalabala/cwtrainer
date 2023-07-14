#ifndef CWTRAINER_CONFIGURATION_TYPES
#define CWTRAINER_CONFIGURATION_TYPES

#include <string>

#define toStr(name) #name

namespace configuration
{
    /**
     * Difficulty of the exercises
    */
    enum Difficulty
    {
        /**
         * Letters (this difficulty requires no dictionary file)
        */
        easy=0,
        /**
         * Words
        */
        medium,
        /**
         * Sentences
        */
        hard
    };

    /**
     * Configuration keys to access their values
    */
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

    /**
     * String equivalents of the above defined ConfigurationKey enum
    */
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
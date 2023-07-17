#ifndef CWTRAINER_DICTIONARY_H
#define CWTRAINER_DICTIONARY_H
#include "../configuration/configuration.h"
#include <memory>
#include <string>
#include <vector>
namespace dictionary
{
    class Dictionary
    {
    public:
        explicit Dictionary(std::shared_ptr<configuration::Configuration> configuration);
        /**
         * Gets the next n tokens in random order, but without repetition if possible.
         * If all the tokens have been traversed, than reshuffles them and starts over
         * (in this case there is a possibility of repetition)
        */
        std::vector<std::string> getNextTokens(int n);

    private:
        std::string getDictionaryPath();
        void shuffle();

        std::vector<std::string> allTokens;
        std::shared_ptr<configuration::Configuration> configuration;

        int lastTokenCount = 0;

        const std::string dictionaryPathBase = "dictionary_";
        const std::string dictionaryPathExt = ".csv";
        const char tokenSeparator = ';';
    };
}

#endif
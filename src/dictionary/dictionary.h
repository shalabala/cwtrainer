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
        Dictionary(std::shared_ptr<configuration::Configuration> configuration);
        std::vector<std::string> getNextTokens(int tokenCount);
    private:
        std::shared_ptr<configuration::Configuration> configuration;
    };
}

#endif
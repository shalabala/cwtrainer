#include "dictionary.h"
#include "../configuration/configuration.h"
#include "../configuration/configuration_types.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>

namespace dictionary
{
    Dictionary::Dictionary(std::shared_ptr<configuration::Configuration> configuration) : configuration(configuration)
    {
        configuration::Difficulty difficulty = static_cast<configuration::Difficulty>(configuration->get<configuration::defaultDifficulty>());

        if (difficulty == configuration::easy)
        {
            for (char c = 'A'; c <= 'Z'; ++c)
            {
                allTokens.push_back(std::string(1, c));
            }
            for (char c = '0'; c <= '9'; ++c)
            {
                allTokens.push_back(std::string(1, c));
            }
        }
        else
        {
            std::string path = getDictionaryPath();
            std::ifstream file(path);
            std::string line;
            std::string token;
            while (std::getline(file, line))
            {
                std::stringstream lineStream(line);
                while (std::getline(lineStream, token, tokenSeparator))
                {
                    allTokens.push_back(token);
                }
            }
        }
        shuffle();
    }

    std::vector<std::string> Dictionary::getNextTokens(int tokenCount)
    {
        std::vector<std::string> retList;
        int end = lastTokenCount + tokenCount;
        while (lastTokenCount < end)
        {
            for (; lastTokenCount < end && lastTokenCount < allTokens.size(); ++lastTokenCount)
            {
                retList.push_back(allTokens[lastTokenCount]);
            }
            // we have reached the end without giving back enough tokens
            //  -> reshuffle and add the remaining
            if (lastTokenCount < end)
            {
                end = end-lastTokenCount;
                lastTokenCount = 0;
                shuffle();
            }
        }
        return std::move(retList);
    }

    std::string Dictionary::getDictionaryPath()
    {
        configuration::Difficulty difficulty = static_cast<configuration::Difficulty>(configuration->get<configuration::defaultDifficulty>());
        return std::string(dictionaryPathBase) +
               std::to_string(difficulty) + dictionaryPathExt;
    }
    void Dictionary::shuffle()
    {
        auto rd = std::random_device{};
        auto rng = std::default_random_engine{rd()};
        std::shuffle(allTokens.begin(), allTokens.end(), rng);
    }
}

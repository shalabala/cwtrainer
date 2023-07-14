#ifndef CWTRAINER_CONFIGURATION_H
#define CWTRAINER_CONFIGURATION_H
#include "configuration_types.h"
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

namespace configuration
{
    class Configuration
    {
    public:
        Configuration();
        template<typename T, ConfigurationKey K>
        T get();
    private:
        template<typename T>
        T setWithoutSave(ConfigurationKey key);
        void readConfigFile();
        void saveConfigFile();
        /**
         * Creates a default config file if the config file does not exist. 
         * Returns true if there was in fact a new file created
         * 
        */
        bool createDefaultConfigFileIfNotExist();
        void createDefaultConfigFile();

        boost::property_tree::ptree config;
    private:
        const std::string dotLengthKey= "dotLength";
        const std::string defaultDificultyKey = "defaultDificulty";
        const std::string beeperFrequencyKey = "beeperFrequency";
        const std::string beeperAmplitudeKey = "beeperAmplitude";
        const std::string singleKeyScanCodeKey = "singleKeyScanCode";
        const std::string dotKeyScanCodeKey = "dotKeyScanCode";
        const std::string dashKeyScanCodeKey = "dashKeyScanCode";

        const std::string path = "cwtrainer.config.json";
    };

}
#include "configuration.tpp"
#endif
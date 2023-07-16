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
        explicit Configuration();
        /**
         * Gets the configuration value and tries to convert it to the given type
         * Note: not all configuration values come from files, some are calculated
        */
        template<typename T, ConfigurationKey K>
        T get();

        template<ConfigurationKey K, typename T>
        void set(T t);

        /**
         * Gets the configuration value and tries to convert it to int
         * Note: not all configuration values come from files, some are calculated
        */
        template<ConfigurationKey K>
        int get();
    private:
        template<typename T>
        void setWithoutSave(ConfigurationKey key, T value);
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
        const std::string path = "cwtrainer.config.json";
    };

}
#include "configuration.tpp"
#endif
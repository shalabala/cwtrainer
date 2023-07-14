#include "configuration.h"
#include "configuration_types.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <filesystem>
#include <iostream>

namespace configuration
{
    inline Configuration::Configuration()
    {
        if (!createDefaultConfigFileIfNotExist())
        {
            readConfigFile();
        }
    }

    template <typename T, ConfigurationKey K>
    inline T Configuration::get()
    {
        try
        {
            return config.get<T>(keyToString[K]);
        }
        catch (std::exception &ex)
        {
            std::cout << "Error while trying to read configuration for key " << keyToString[K]
                      << " std::exception: " << ex.what() << std::endl;
            std::cout << "Recreating and saving new configuration file" << std::endl;
            createDefaultConfigFile();
            return config.get<T>(keyToString[K]);
        }
    }

    template <>
    inline int Configuration::get<int, dashLength>()
    {
        return get<int, dotLength>() * 3;
    }

    template <ConfigurationKey K>
    inline int Configuration::get()
    {
        return get<int, K>();
    }

    template <>
    inline int Configuration::get<int, wordEndLength>()
    {
        return get<int, dotLength>() * 7;
    }

    template <>
    inline int Configuration::get<int, letterEndLength>()
    {
        return get<int, dotLength>() * 3;
    }

    template <>
    inline int Configuration::get<int, dashThresholdLength>()
    {
        return get<int, dashLength>() / 2;
    }

    inline bool Configuration::createDefaultConfigFileIfNotExist()
    {
        if (std::filesystem::exists(path))
        {
            return false;
        }
        createDefaultConfigFile();
        return true;
    }
    inline void Configuration::createDefaultConfigFile()
    {
        config.clear();
        setWithoutSave(dotLength, 150);
        setWithoutSave(defaultDifficulty, medium);
        setWithoutSave(beeperFrequency, 550);
        setWithoutSave(beeperAmplitude, 28000);
        setWithoutSave(singleKeyScanCode, 32);
        setWithoutSave(dotKeyScanCode, 70);
        setWithoutSave(dashKeyScanCode, 71);
        saveConfigFile();
    }

    inline void Configuration::saveConfigFile()
    {
        boost::property_tree::write_json(path, config);
    }

    inline void Configuration::readConfigFile()
    {
        boost::property_tree::read_json(path, config);
    }

    template <typename T>
    void Configuration::setWithoutSave(ConfigurationKey key, T value)
    {
        config.put(keyToString[key], value);
    }

}
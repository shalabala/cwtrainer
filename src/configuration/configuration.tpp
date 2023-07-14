#include "configuration.h"
#include "configuration_types.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <filesystem>

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
        return config.get<T>(keyToString[K]);
    }

    template <>
    inline int Configuration::get<int, dashLength>()
    {
        return get<int, dotLength>() * 3;
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
    inline int Configuration::get<int,dashThresholdLength>()
    {
        return get<int,dashLength>()/2;
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
        config.put(dotLengthKey, 150);
        config.put(defaultDificultyKey, medium);
        config.put(beeperFrequencyKey, 550);
        config.put(beeperAmplitudeKey, 28000);
        config.put(singleKeyScanCodeKey, 32);
        config.put(dotKeyScanCodeKey, 70);
        config.put(dashKeyScanCodeKey, 71);
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

}
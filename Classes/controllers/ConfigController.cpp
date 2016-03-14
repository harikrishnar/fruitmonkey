//
//  ConfigController.cpp
//  page3
//
//  Created by Hari Krishna on 11/24/15.
//
//

#include "ConfigController.h"


//struct order_by_level
//{
//    inline bool operator() (ValueMap& map1,ValueMap& map2)
//    {
//        return false;
//        return map1["level"].asInt() > map2["level"].asInt();
//    }
//};

ConfigController* ConfigController::_instance = nullptr;

ConfigController::ConfigController() {}

void ConfigController::initListeners(Ref *target) {};
void ConfigController::removeListeners() {};
void ConfigController::registerListener(Ref *target, const char *event) {};
void ConfigController::deregisterListener(const char *event) {};

ConfigController* ConfigController::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new (std::nothrow) ConfigController();
        if(!_instance->init())
        {
            delete _instance;
            _instance = nullptr;
            CCLOG("ERROR: Could not init ConfigController");
        }
    }
    return _instance;
}

ValueMap& ConfigController::getConfig(std::string configName) {
    CCASSERT(_configs.find(configName) != _configs.end(), "Config doesn't exist");
    return _configs[configName];
}

ValueMap ConfigController::readConfig(const std::string& configFileName) {
    ValueMap ans;
    if (!FileUtils::getInstance()->fullPathForFilename(configFileName + ".json").empty()) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    ans = JsonController::getValueMapFromJsonFile(configFileName + ".json");
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    ans = JsonController::getValueMapFromJsonFile(configFileName + ".json", true);
#else
    ans = JsonController::getValueMapFromJsonFile(configFileName + ".json", true);
#endif
    } else {
        CCLOG("ERROR: Critical: Coudln't load config %s", configFileName.c_str());
    }
    return ans;
}

Value ConfigController::getValueForKeyInConfig(std::string key, std::string config) {
    ValueMap& v = this->getConfig(config);
    if (v.find(key) != v.end()) {
        return v[key];
    }
    return Value::Null;
}

std::string ConfigController::getStringValueForKeyInConfig(std::string key, std::string config) {
    ValueMap& v = this->getConfig(config);
    if (v.find(key) != v.end() && v[key].getType() == cocos2d::Value::Type::STRING){
        return v[key].asString();
    }
    return Value::Null.asString();
}

int ConfigController::getIntValueForKeyInConfig(std::string key, std::string config) {
    ValueMap& v = this->getConfig(config);
    if (v.find(key) != v.end() && v[key].getType() == cocos2d::Value::Type::INTEGER) {
        return v[key].asInt();
    }
    return Value::Null.asInt();
}

ValueVector ConfigController::getVectorValueForKeyInConfig(std::string key, std::string config)
{
    ValueMap& v = this->getConfig(config);
    if (v.find(key) != v.end() && v[key].getType() == cocos2d::Value::Type::VECTOR) {
        return v[key].asValueVector();
    }
    return Value::Null.asValueVector();
}

ValueMap ConfigController::getMapValueForKeyInConfig(std::string key, std::string config)
{
    ValueMap& v = this->getConfig(config);
    if (v.find(key) != v.end() && v[key].getType() == cocos2d::Value::Type::MAP ) {
        return v[key].asValueMap();
    }
    return Value::Null.asValueMap();
}

void ConfigController::loadConfig(const std::string& configFileName) {
    _configs[configFileName] = this->readConfig(configFileName);
}

bool ConfigController::init() {

//    _configs[ConfigNames::Transition] = this->readConfig(ConfigNames::Transition)["transitionGroups"].asValueMap();
//
//    this->loadConfig(ConfigNames::Character);
    return true;
}

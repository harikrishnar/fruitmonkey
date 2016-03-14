//
//  ConfigController.h
//  page3
//
//  Created by Hari Krishna on 11/24/15.
//
//

#ifndef ConfigController_h
#define ConfigController_h

#include <stdio.h>
#include "cocos2d.h"
#include "JsonController.h"

class ConfigController
{
private:
    ConfigController();
    std::unordered_map<std::string, ValueMap> _configs;
    static ConfigController* _instance;
    ValueMap npcById;
public:
    static ConfigController* getInstance();
    void initListeners(Ref *target);
    void removeListeners();
    void registerListener(Ref *target, const char *event);
    void deregisterListener(const char *event);
    ValueMap& getConfig(std::string);
    cocos2d::Value getValueForKeyInConfig(std::string key, std::string config);
    std::string getStringValueForKeyInConfig(std::string key, std::string config);
    int getIntValueForKeyInConfig(std::string key, std::string config);
    ValueVector getVectorValueForKeyInConfig(std::string key, std::string config);
    ValueMap getMapValueForKeyInConfig(std::string key, std::string config);
    bool init();
    void loadConfig(const std::string& configFileName);
    ValueMap readConfig(const std::string& configFileName);
};

#endif /* ConfigController_h */

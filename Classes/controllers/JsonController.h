//
//  JsonController.h
//  page3
//
//  Created by Hari Krishna on 11/19/15.
//
//

#ifndef JsonController_h
#define JsonController_h

#include <stdio.h>
#pragma once

#include "cocos2d.h"
#include <json/document.h>
#include <json/rapidjson.h>
#include <json/prettywriter.h>

USING_NS_CC;

class JsonController
{
public:
    static cocos2d::Value parseValueFromJsonValue(const rapidjson::Value& jvalue);
    static cocos2d::ValueMap getValueMapFromJsonFile(const std::string& filename, bool isEncrpted = false);
    static cocos2d::ValueVector getValueVectorFromJsonFile(const std::string& filename);
    static void recurseRapidJson(rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<> > >& writter, cocos2d::Value value);
    static cocos2d::ValueMap getValueMapFromJson(std::string);
    static cocos2d::ValueVector getValueVectorFromJson(std::string);
    static cocos2d::Value getValueFromJson(std::string);
    static std::string getJsonStringFromValueMap(ValueMap value);
    static std::string getJsonStringFromValueVector(ValueVector);
    
};

#endif /* JsonController_h */

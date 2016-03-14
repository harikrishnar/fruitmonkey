//
//  JsonController.cpp
//  page3
//
//  Created by Hari Krishna on 11/19/15.
//
//

#include "JsonController.h"
#include <json/rapidjson.h>
#include "cocos2d.h"

//USING_NS_CC;
//using namespace cocostudio;

// TODO: add any necessary 'const', 'const' & references, or error checking
cocos2d::Value JsonController::parseValueFromJsonValue(const rapidjson::Value& jvalue)
{
    // parse by type
    auto t = jvalue.GetType();

    if(t == rapidjson::Type::kNullType)
    {
        // don't add anything
        return cocos2d::Value();
    }

    if(t == rapidjson::Type::kFalseType) {
        return cocos2d::Value(false);
    }

    if(t == rapidjson::Type::kTrueType) {
        return cocos2d::Value(true);
    }

    if(t == rapidjson::Type::kStringType) {
        return cocos2d::Value(jvalue.GetString());
    }

    if(t == rapidjson::Type::kNumberType) {
        if(jvalue.IsDouble()) {
            return cocos2d::Value(jvalue.GetDouble());
        } else if(jvalue.IsUint()) {
            int temp = int(jvalue.GetUint());
            return cocos2d::Value(temp);
        } else if(jvalue.IsInt()) {
            return cocos2d::Value(jvalue.GetInt());
        } else if (jvalue.IsInt64()) {
            return cocos2d::Value(jvalue.GetInt());
        }
    }

    if(t == rapidjson::Type::kObjectType) {
        cocos2d::ValueMap dict;
        for (rapidjson::Value::ConstMemberIterator itr = jvalue.MemberBegin(); itr != jvalue.MemberEnd(); ++itr)
        {
            auto jsonKey = itr->name.GetString();
            auto el = parseValueFromJsonValue(itr->value);
            dict[jsonKey] = el;
        }
        return cocos2d::Value(dict);
    }
    if(t == rapidjson::Type::kArrayType) {
        cocos2d::ValueVector arr;
        // rapidjson uses SizeType instead of size_t.
        for (rapidjson::SizeType i = 0; i < jvalue.Size(); i++) {
            auto el = parseValueFromJsonValue(jvalue[i]);
            arr.push_back(el);
        }
        return cocos2d::Value(arr);
    }

    // none
    return cocos2d::Value();
}

cocos2d::ValueMap JsonController::getValueMapFromJsonFile(const std::string& filename, bool isEncrypted /* = false */)
{
    auto content = cocos2d::FileUtils::getInstance()->getStringFromFile(filename);
    return JsonController::getValueMapFromJson(content);
}

cocos2d::ValueVector JsonController::getValueVectorFromJsonFile(const std::string& filename)
{
    auto content = cocos2d::FileUtils::getInstance()->getStringFromFile(filename);
    return JsonController::getValueVectorFromJson(content);
}

cocos2d::ValueMap JsonController::getValueMapFromJson(std::string content) {
    auto val = JsonController::getValueFromJson(content);
    if(val.getType() == cocos2d::Value::Type::MAP) {
        return val.asValueMap();
    }
    CCLOGERROR("content wasnt valuemap");

    cocos2d::ValueMap ret;
    return ret;
}

cocos2d::ValueVector JsonController::getValueVectorFromJson(std::string content) {
    auto val = JsonController::getValueFromJson(content);
    if(val.getType() == cocos2d::Value::Type::VECTOR) {
        return val.asValueVector();
    }
    CCLOGERROR("content wasnt valuevector");
    cocos2d::ValueVector ret;
    return ret;
}

cocos2d::Value JsonController::getValueFromJson(std::string content) {
    rapidjson::Document doc;
    doc.Parse<0>(content.c_str());
    if (! doc.HasParseError())
    {
        // check that root is object not array
        auto val = parseValueFromJsonValue(doc);
        if(!val.isNull()) {
            return val;
        }
        CCLOGERROR("content wasnt aj json string");
    }

    CCLOG("Inderpal JSON Parse Error: %u\n", doc.GetParseError());

    cocos2d::Value ret;
    return ret;
}

void JsonController::recurseRapidJson(rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<> > >& writter, Value value) {
    auto type = value.getType();

    if (type == cocos2d::Value::Type::BOOLEAN) {
        writter.Bool(value.asBool());
        return;
    }
    if (type == cocos2d::Value::Type::INTEGER) {
        writter.Int(value.asInt());
        return;
    }
    if (type == cocos2d::Value::Type::FLOAT) {
        writter.Double((double)value.asFloat());
        return;
    }
    if (type == cocos2d::Value::Type::DOUBLE) {
        writter.Double(value.asDouble());
        return;
    }
    if (type == cocos2d::Value::Type::STRING) {
        writter.String(value.asString().c_str());
        return;
    }
    if (type == cocos2d::Value::Type::VECTOR) {
        writter.StartArray();
        ValueVector vec = value.asValueVector();
        for (int i = 0; i < vec.size(); i++) {
            JsonController::recurseRapidJson(writter, vec[i]);
        }
        writter.EndArray();
        return;
    }
    if (type == cocos2d::Value::Type::MAP) {
        writter.StartObject();
        ValueMap map = value.asValueMap();
        ValueMap::iterator itr = map.begin();
        for (; itr != map.end(); itr++) {
            writter.String(itr->first.c_str());
            JsonController::recurseRapidJson(writter, itr->second);
        }
        writter.EndObject();
        return;
    }
}

std::string JsonController::getJsonStringFromValueMap(ValueMap map) {
    rapidjson::GenericStringBuffer<rapidjson::UTF8<> > ss;
    rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<> > > writer(ss);

    writer.StartObject();
    ValueMap::iterator itr = map.begin();
    for (; itr != map.end(); itr++) {
        writer.String(itr->first.c_str());
        JsonController::recurseRapidJson(writer, itr->second);
    }
    writer.EndObject();

    return ss.GetString();
}

std::string JsonController::getJsonStringFromValueVector(ValueVector map) {
    rapidjson::GenericStringBuffer<rapidjson::UTF8<> > ss;
    rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<> > > writer(ss);

    writer.StartArray();
    for (int i = 0; i < map.size(); i++) {
        JsonController::recurseRapidJson(writer, map[i]);
    }
    writer.EndArray();

    return ss.GetString();
}
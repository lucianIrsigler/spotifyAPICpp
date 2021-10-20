#pragma once

#include "json/json.h"
#include <string>

namespace json
{
    /*
    */
    static std::string convertToJSONString(std::string&& jsonFormat, std::vector<std::string>& values) {
        //{1:[2,3,4]}
        //{1:[{2:3},{2:3}]}
        std::string temp = "";    

        for (size_t i = 0; i < jsonFormat.length(); i++) {
            if (std::isdigit(jsonFormat[i])) {
                int x = std::stoi(std::string(1, jsonFormat[i]));
                temp += values[x];
            }
            else {
                temp += jsonFormat[i];
            }

        }
        return temp;
    }

    /**/
    static std::string convertToJSONObject(std::string value) {

        Json::CharReaderBuilder builder;
        Json::CharReader* reader = builder.newCharReader();

        Json::Value root;
        std::string errors;

        bool parsingSuccessful = reader->parse(value.c_str(), value.c_str() + value.size(), &root, &errors);
        delete reader;

        if (!parsingSuccessful)
        {
            std::cout << value << std::endl;
            std::cout << "ERRORS:" << errors << std::endl;
        }

        for (Json::Value::const_iterator outer = root.begin(); outer != root.end(); outer++)
        {
            for (Json::Value::const_iterator inner = (*outer).begin(); inner != (*outer).end(); inner++)
            {
                //std::cout << inner.key() << ": " << *inner << std::endl;
                ;
            }
        }

        return value;
    }

};


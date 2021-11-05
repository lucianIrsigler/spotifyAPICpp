#pragma once

#include "json/json.h"
#include <string>

namespace json
{
    /*
        Converts a JSON format string into a JSON string with the values from a vector
        @param jsonFormat->format of JSON object. Example: {0:1,2}
        @param values->Values to insert
        @returns string ready to be converted into a JSON object
    */
    static std::string convertToJSONString(std::string jsonFormat, std::vector<std::string>& values) {
        //{1:[2,3,4]}
        //{1:[{2:3},{2:3}]}
        std::string temp = "";    

        for (size_t i = 0; i < jsonFormat.length(); i++) {
            if (std::isdigit(jsonFormat[i])) {
                int x = std::stoi(std::string(1, jsonFormat[i]));
                temp += values[x];
                //If the the digit is '0', then the value at index '0' of the vector is placed there
            }
            else {
                temp += jsonFormat[i];
            }

        }
        return temp;
    }

    /*
        Converts a string into a JSON object
        @param value->string to be converted
        @returns JSON object
    */
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

        //for (Json::Value::const_iterator outer = root.begin(); outer != root.end(); outer++)
        //{
        //    for (Json::Value::const_iterator inner = (*outer).begin(); inner != (*outer).end(); inner++)
        //    {
        //        //std::cout << inner.key() << ": " << *inner << std::endl;
        //        ;
        //    }
        //}

        return value;
    }

};


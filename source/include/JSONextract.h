/*
    APIextract.h
    Purpose: Extract value from key-value pairs in JSON string

    @author Lucian Irsigler
    @version 1.0 06/05/2022

*/

#pragma once
#include <string>
/*
    Extracts a value from JSON format based on the key provided
    @param JSON-> JSON to search through
    @param key->key to look for
    @param start->Starting index
    @param constantAdd->Number to add to firstIndex to get the correct value. Defaults to 4 for most Spotify API json, some need 3
    @returns value
*/
static const std::string extractValueFromString(std::string& JSON, std::string&& key, int start = 0, int constantAdd = 4) noexcept;

/*
    Extracts a value from JSON format based on the key provided
    @param JSON-> JSON to search through
    @param key->key to look for
    @param start->Starting index
    @param constantAdd->Number to add to firstIndex to get the correct value. Defaults to 4 for most Spotify API json, some need 3
    @returns value
*/
static const std::string extractNumberFromString(std::string& JSON, std::string&& key, int start = 0, int constantAdd = 4) noexcept;


static const std::string extractValueFromString(std::string& JSON, std::string&& key, int start, int constantAdd) noexcept {
    if (JSON.find(key, start) != std::string::npos) {
        int firstIndex = JSON.find(key, start) + key.length() + constantAdd;
        std::string value = JSON.substr(firstIndex + 1, JSON.find("\"", firstIndex + 5) - firstIndex - 1);
        return value;
    }
    else {
        return "ERROR EXTRACTING JSON VALUE";
    }
}

static const std::string extractNumberFromString(std::string& JSON, std::string&& key, int start, int constantAdd) noexcept {
    if (JSON.find(key, start) != std::string::npos) {
        int firstIndex = JSON.find(key, start) + key.length() + constantAdd;
        std::string value = JSON.substr(firstIndex, JSON.find(",", firstIndex) - firstIndex);
        return value;
    }
    else {
        return "ERROR EXTRACTING NUMBER";
    }
}
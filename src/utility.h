/**
    utility.h
    Purpose: Creates a namespace that contains utility functions for cURL operations and text generation

    @author Lucian Irsigler
    @version 1.0 07/10/2021
*/

#pragma once
#include <string>
#include <iostream>
#include <curl/curl.h>
#include <vector>
#include "json/json.h"

namespace utility{

    /**/
    static std::string generateRandomText(int length) {
        char c;
        std::string message;

        for (uint8_t i = 0; i < length; i++) {
            uint8_t selection = rand() % 2;
            uint8_t random = rand() % 26;

            if (selection == 0) {
                c = 'a' + random;
            }
            else {
                c = 'A' + random;
            }

            message += c;
        }

        return message;
    }

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
    {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    static std::string performCURLGET(std::string website, struct curl_slist* list) {
        CURL* curl;//Initilizes a cURL
        CURLcode res;

        //Buffer to write to
        std::string readBuffer;

        //Initilizes the cURL request
        curl = curl_easy_init();
        if (curl) {

            //Set options

            //Sets URL
            curl_easy_setopt(curl, CURLOPT_URL, website.c_str());

            //Sets writer function
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

            //Sets where to write the data to
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

            //Sets headers
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

            //Performs HTTP GET request
            res = curl_easy_perform(curl);

            //Cleanups process
            curl_easy_cleanup(curl);

            //Returns the buffer
            return readBuffer;
        }
        else {
            return "ERROR: curl failed";
        }
    }

    static std::string performCURLPOST(std::string website, std::string POSTdata,struct curl_slist* list) {
        CURL* curl;
        CURLcode res;

        std::string readBuffer;
        curl_global_init(CURL_GLOBAL_ALL);

        curl = curl_easy_init();

        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, website.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, POSTdata.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
                return "ERROR: HTTP POST request failed";
            }
            curl_easy_cleanup(curl);

            curl_global_cleanup();

            return readBuffer;
        }
        else {
            return "ERROR: curl failed";
        }
    }

    /**/
    static std::string performCURLPUT(std::string website, std::string POSTdata, std::string token) {
        CURL* curl;
        CURLcode res;

        //Used for headers
        struct curl_slist* list = NULL;

        //Required headers
        list = curl_slist_append(list, "Accept: application/json");
        list = curl_slist_append(list, "Content-Type: application/json");
        list = curl_slist_append(list, ("Authorization: Bearer " + token).c_str());

        std::string readBuffer;
        curl_global_init(CURL_GLOBAL_ALL);

        curl = curl_easy_init();

        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, website.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, POSTdata.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
                return "ERROR: HTTP POST request failed";
            }
            curl_easy_cleanup(curl);

            curl_global_cleanup();

            return readBuffer;
        }
        else {
            return "ERROR: curl failed";
        }
    }

    /*
    */
    static std::string convertToJSONString(std::string&& jsonFormat, std::vector<std::string>& values) {
        //{1:[2,3,4]}
        //{1:[{2:3},{2:3}]}
        std::string temp = "";

        for (size_t i = 0; i < jsonFormat.length(); i++) {
            if (std::isdigit(jsonFormat[i])) {
                int x = std::stoi(std::string(1,jsonFormat[i]));
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
            std::cout <<"ERRORS:"<< errors << std::endl;
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

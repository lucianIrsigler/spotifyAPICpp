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
#include "spotifyexception.h"
#include "spotifylogging.h"

namespace utility{
    /*
    Checks if the limit and offset are invalid.
    Limit must be within the range of [1,50).
    Offset must be within the range of [0,10000).
    Inverse of conjunction is returned- as if both statements are true- then the function returns false

    @returns the inverse of the truth Conjunction of the two statements.
*/
    static bool isLimitsAndOffsetInvalid(int limit, int offset) {
        return !((1 <= limit && limit < 50) && (0 <= offset && offset < 10000));
    }

    /*
        Checks if any error has occured
        @returns spotifyException if error has occured
    */
    static void checkConditions(std::string& request) {
        if (request.find("400") != std::string::npos 
            || request.find("403") != std::string::npos
            || request.find("404")!= std::string::npos) 
        {
            int first = request.find("message")+10;
            int second = request.find('"', first)+1;
            throw spotifyException(request.substr(second, request.find('"', second + 1) - second));
        }

        /*std::vector<std::string>errors = { "The access token expired","Permissions missing","Invalid username",
        "Invalid playlist Id","Invalid market code", "You cannot create a playlist for another user.", "Device not found",
        "Not found","invalid request"
        };

        for (auto x : errors) {
            if (request.find(x) != std::string::npos) {
                throw spotifyException("error:" + x);
            }
        }*/
    }

    /*
    */
    static std::string errorChecking(std::string& request, std::string className, std::string functionName) {
        //Returns the buffer
        try {
            utility::checkConditions(request);
            return request;
        }
        catch (const spotifyException& error) {
            spotifyLogToFile(className+"::"+functionName + "->" + error.what());
            return error.what();
        }
    }

    static void errorChecking(std::string& request, std::string className, std::string functionName, bool canLog) {
        //Returns the buffer
        try {
            utility::checkConditions(request);
        }
        catch (const spotifyException& error) {
            if (canLog) {
                std::cout << "OKAY and" << std::endl;
                spotifyLogToFile(className + "::" + functionName + "->" + error.what());
            }
        }
    }

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

    /**/
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
    {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    /**/
    static std::string performCURLGET(std::string website, std::string token) {
        CURL* curl;//Initilizes a cURL
        CURLcode res;

        //Used for headers
        struct curl_slist* list = NULL;

        //Required headers
        list = curl_slist_append(list, "Accept: application/json");
        list = curl_slist_append(list, "Content-Type: application/json");
        list = curl_slist_append(list, ("Authorization: Bearer " + token).c_str());

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

            return readBuffer;
        }
        else {
            return "ERROR: curl failed";
        }
    }

    /**/
    static std::string performCURLPOST(std::string website, std::string POSTdata,std::string token) {
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
    static std::string performCURLPOST(std::string website, std::string POSTdata, struct curl_slist* list) {
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

    /**/
    static std::string performCURLDELETE(std::string website, std::string POSTdata, std::string token) {
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
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

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
};

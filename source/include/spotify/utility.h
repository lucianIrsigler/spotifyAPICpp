/**
    utility.h
    Purpose: Creates a namespace that contains utility functions for cURL operations and text generation

    @author Lucian Irsigler
    @version 1.0 07/10/2021
*/

#pragma once
#include <vector>
#include "spotifyexception.h"
#include "spotifylogging.h"

//Functions for utility->error checking/condition checking
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
        @param request->API request to check
        @returns spotifyException if error has occured
    */
    static void checkConditions(std::string& request) {
        if (request.find("error")!=std::string::npos)
        {
            int first = request.find("message")+10;
            int second = request.find('"', first)+1;
            throw spotifyException(request.substr(second, request.find('"', second + 1) - second));
        }
    }
    
    /*
        Checks if the request has any errors then logs the function name to SPOTIFYLOG.txt
        @param request-> API returning text
        @param functionName->function name to log
        @returns request or the error message
    */
    static std::string errorChecking(std::string& request,std::string functionName) {
        //Returns the buffer
        
        try {
            utility::checkConditions(request);
            return request;
        }
        catch (const spotifyException& error) {
            spotifyLogToFile(functionName + "->" + error.what());
            return error.what();
        }
    }

    /*
        Checks if the request has any errors then logs the function name to SPOTIFYLOG.txt
        @param request-> API returning text
        @param className->class the function belongs to
        @param functionName->function name to log
        @returns request or the error message
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

    /*
        Checks if the request has any errors then logs the function name to SPOTIFYLOG.txt. Used for functions
        @param request-> API returning text
        @param className->class the function belongs to
        @param functionName->function name to log
        @returns request or the error message
    */
    static void errorChecking(std::string& request, std::string className, std::string functionName, bool canLog) {
        //Returns the buffer
        try {
            utility::checkConditions(request);
        }
        catch (const spotifyException& error) {
            if (canLog) {
                spotifyLogToFile(className + "::" + functionName + "->" + error.what());
            }
        }
    }

    /*
        Generates a random text of n length
        @param length->length of text to generate
        @returns random text
    */
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
};

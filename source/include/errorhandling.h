/*
    errorhandling.h
    Purpose: Contains error handling methods

    @author Lucian Irsigler
    @version 1.0 19/01/2022

*/

#pragma once
#include <string>
#include <algorithm>
#include "spotifyexception.h"
#include "logging.h"
#include "JSONextract.h"

/*
    Checks if the request has any errors then logs the function name to SPOTIFYLOG.txt
    @param request-> API returning text
    @param className->class the function belongs to
    @param functionName->function name to log
    @returns request or the error message
*/
inline std::string errorChecking(std::string& request, std::string functionName) {
    //Returns the buffer
    try {
        if (request.find("error") != std::string::npos)
        {
            std::string errorMessage = extractValueFromString(request, "message", 0, 3);
            std::replace(errorMessage.begin(), errorMessage.end(), '\"', ' ');

            throw spotifyException(errorMessage);
        }
        return request;
    }
    catch (const spotifyException& error) {
        spotifyLogToFile(functionName + "->" + error.what());
        return error.what();
    }
}


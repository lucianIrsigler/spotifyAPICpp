/*
	errorhandling.h
	Purpose: Contains error handling methods

	@author Lucian Irsigler
	@version 1.0 19/01/2022

*/

#pragma once
#include <string>
#include "spotifyexception.h"
#include "spotifylogging.h"


/*
    Checks if the request has any errors then logs the function name to SPOTIFYLOG.txt
    @param request-> API returning text
    @param className->class the function belongs to
    @param functionName->function name to log
    @returns request or the error message
*/
inline std::string errorChecking(std::string& request,std::string functionName) {
    //Returns the buffer
    try {
        if (request.find("error") != std::string::npos)
        {
            int messageFieldIndex = request.find("message") + 10;
            int messageStartIndex = request.find('"', messageFieldIndex) + 1;
            int messsageEndIndex = request.find('"', messageStartIndex + 1);

            throw spotifyException(request.substr(messageStartIndex, messsageEndIndex - messageStartIndex));
        }
        return request;
    }
    catch (const spotifyException& error) {
        spotifyLogToFile(functionName + "->" + error.what());
        return (error.what());
    }
}

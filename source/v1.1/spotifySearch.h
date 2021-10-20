#pragma once
#include <string>
#include "utility.h"
#include "spotifylogging.h"

/*
*/
std::string searchSpotify(std::string q, std::string type, std::string market, int limit = 20, int offset = 0, std::string token ="") {
    std::string fields = "album artist playlist track show episode";

    if (utility::isLimitsAndOffsetInvalid(limit, offset)) {
        spotifyLogToFile("searchSpotify->Invalid limit/offset.\nLimit:" + std::to_string(limit) + "\nOffset:" + std::to_string(offset));
        throw spotifyException("ERROR: Invalid limit/offset");
    }
    else if (fields.find(type)!=std::string::npos){
        spotifyLogToFile("spotifyFollowers::unfollowArist()->Invalid type\ntype:" + type);
        return;
    }

    std::string url = "https://api.spotify.com/v1/search?q=" + q
        + "&type=" + type;

    if (market != "") {
        url += "&market=" + market; 
    }

    url += "&limit=" + std::to_string(limit) + "&offset=" + std::to_string(offset);
    
    std::string readBuffer = utility::performCURLGET(url, token);

    try {
        utility::checkConditions(readBuffer);
        return readBuffer;
    }
    catch (const spotifyException& error) {
        spotifyLogToFile(error.what());
        return error.what();
    }
}
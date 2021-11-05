#pragma once
#include <string>
#include "spotifylogging.h"
#include "utility.h"
#include "HTTPrequests.h"

/*
    Performs a search query
    @param q->search query
    @param type->
    @param token->Auth token
    @param market->Specific market to look for
    @param limit->Number of searchs to return
    @param offset->Offset from first search
    @returns JSON response body encompassing the search
*/
std::string searchSpotify(std::string q, std::string type, std::string token = "", std::string market = "", int limit = 20, int offset = 0) {
    std::string fields = "album artist playlist track show episode";

    if (utility::isLimitsAndOffsetInvalid(limit, offset)) {
        spotifyLogToFile(std::string(__func__) + "->Invalid limit/offset.\nLimit:" + std::to_string(limit) + "\nOffset: " + std::to_string(offset));
        return "invalid limit/offset";
    }
    else if (fields.find(type)==std::string::npos){
        spotifyLogToFile(std::string(__func__)+"->Invalid type\ntype:" + type);
        return "invalid type";
    }

    std::string url = "https://api.spotify.com/v1/search?q=" + q
        + "&type=" + type;

    if (market != "") {
        url += "&market=" + market; 
    }

    url += "&limit=" + std::to_string(limit) + "&offset=" + std::to_string(offset);
    
    std::string readBuffer = performCURLGET(url, token);

    return utility::errorChecking(readBuffer,__func__);
}
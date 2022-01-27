#pragma once
#include <string>
#include "spotifylogging.h"
#include "misc.h"
#include "HTTPrequests.h"
#include "errorhandling.h"



/*
    Performs a search query
    @param q->search query
    @param type-> type of search(album artist playlist track show episode)
    @param token->Auth token
    @param market->Specific market to look for
    @param limit->Number of searchs to return
    @param offset->Offset from first search
    @returns JSON response body encompassing the search
*/
inline std::string searchSpotify(std::string query, std::string type, std::string token = "", std::string market = "", int limit = 20, int offset = 0) {
    std::string fields = "album artist playlist track show episode";

    if (isLimitsAndOffsetInvalid(limit, offset)) {
        spotifyLogToFile(std::string(__func__) + "->Invalid limit/offset.\nLimit:" + std::to_string(limit) + "\nOffset: " + std::to_string(offset));
        return "invalid limit/offset";
    }
    else if (fields.find(type)==std::string::npos){
        spotifyLogToFile(std::string(__func__)+"->Invalid type\ntype:" + type);
        return "invalid type";
    }

    for (size_t pos = query.find(' ');
        pos != std::string::npos;
        pos = query.find(' ', pos))
    {
        query.replace(pos, 1, "%20");
    }

    std::string url = "https://api.spotify.com/v1/search?q=" + query
        + "&type=" + type;

    if (market != "") {
        url += "&market=" + market; 
    }
    
    url +="&limit=" + std::to_string(limit)
        + "&offset=" + std::to_string(offset);

    std::string readBuffer = performCURLGET(url, token);

    return errorChecking(readBuffer,__func__);
}
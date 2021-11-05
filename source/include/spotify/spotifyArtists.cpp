#include "spotifyArtists.h"

std::string spotifyArtists::getArtistAlbums(std::string ID, std::string include_groups, std::string market, int limit, int offset){

    std::string validIncludeGroups = "album single appears_on compilation";

    if (utility::isLimitsAndOffsetInvalid(limit, offset)) {
        spotifyLogToFile(__class__ + "::" + std::string(__func__) + "->Invalid limit/offset.\nLimit:" + std::to_string(limit) + "\nOffset: " + std::to_string(offset));
        return "invalid limit/offset";
    }
    else if (validIncludeGroups.find(include_groups) == std::string::npos) {
        spotifyLogToFile(__class__ + "::" + std::string(__func__) + "->Invalid type\ntype:" + include_groups);
        return "invalid include_groups";
    }

    std::string url = "https://api.spotify.com/v1/artists/" + ID + "/albums";

    if (include_groups != "") {
        url += "?include_groups=" + include_groups;
        if (market != "") {
            url += "&market=" + market;
            url += "&limit=" + std::to_string(limit) + "&offset=" + std::to_string(offset);
        }
    }else if (market != "") {
        url += "?market=" + market;
        url += "&limit=" + std::to_string(limit) + "&offset=" + std::to_string(offset);
    }

    std::string readBuffer = performCURLGET(url, spotifyAuthenticityToken);

    return utility::errorChecking(readBuffer, __class__, __func__);

}

std::string spotifyArtists::getArtistRelatedArtists(std::string ID){
    //https://developer.spotify.com/console/get-artist-related-artists/
    std::string url = "https://api.spotify.com/v1/artists/" + ID + "/related-artists";


    std::string readBuffer = performCURLGET(url, spotifyAuthenticityToken);

    return utility::errorChecking(readBuffer, __class__, __func__);
}


std::string spotifyArtists::getArtistTopTracks(std::string ID, std::string market){
    //https://developer.spotify.com/console/get-artist-top-tracks/


    std::string url = "https://api.spotify.com/v1/artists/" + ID + "/top-tracks";

    if (market != "") {
        url += "?market=" + market;
    }

    std::string readBuffer = performCURLGET(url, spotifyAuthenticityToken);

    return utility::errorChecking(readBuffer, __class__, __func__);
}

std::string spotifyArtists::getArtist(std::string ID){
    //https://developer.spotify.com/console/get-artist/

    std::string url = "https://api.spotify.com/v1/artists/" + ID;

    std::string readBuffer = performCURLGET(url, spotifyAuthenticityToken);

    return utility::errorChecking(readBuffer, __class__, __func__);
}

std::string spotifyArtists::getArtists(std::string IDs){
//https://developer.spotify.com/console/get-several-artists/

    std::string url = "https://api.spotify.com/v1/artists?ids=" + IDs;

    std::string readBuffer = performCURLGET(url, spotifyAuthenticityToken);

    return utility::errorChecking(readBuffer, __class__, __func__);
}
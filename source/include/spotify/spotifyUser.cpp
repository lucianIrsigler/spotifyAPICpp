#include "spotifyUser.h"

spotifyUser::spotifyUser() :base()
{
    _className = __class__;
};

spotifyUser::spotifyUser(
    std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect) :
    base(authToken, userspotifyClientID, userClientSecret, userRedirect)
{
    spotifyLogToFile("Created:" + __class__);
    _className = __class__;
};

spotifyUser::spotifyUser(spotifyInfo* clientInformation) :
    base(clientInformation)
{
    spotifyLogToFile("Created:" + __class__);
    _className = __class__;
};

std::string spotifyUser::getUserInfo() {

    //acquires user data and stores in variable readBuffer
    std::string readBuffer = performCURLGET("https://api.spotify.com/v1/me", spotifyAuthenticityToken);

    //checks readBuffer and returns right value
    return utility::errorChecking(readBuffer, __class__, __func__);
}

std::string spotifyUser::getDisplayName() {
    std::string userInfo = getUserInfo();
    std::cout << userInfo << std::endl;
    return userInfo.substr(22, userInfo.find('"', 22) - 22);
}


std::string spotifyUser::getUserURL() {
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"spotify\"") + 13;
    return userInfo.substr(first, userInfo.find('"', first) - first);
}


int spotifyUser::getUserFollowers() {
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"total\"") + 10;
    std::string followers = userInfo.substr(first, userInfo.find('}', first) - first);
    return std::stoi(followers);
}


std::string spotifyUser::getUserID() {
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"id\"") + 8;
    return userInfo.substr(first, userInfo.find('"', first) - first);
}


std::string spotifyUser::getUserProfilePictureURL() {
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"url\"") + 9;
    return userInfo.substr(first, userInfo.find('"', first) - first);
}


std::string spotifyUser::getUserType() {
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"type\"") + 10;
    return userInfo.substr(first, userInfo.find('"', first) - first);
}


std::string spotifyUser::getUserURI() {
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"uri\"") + 9;
    return userInfo.substr(first, userInfo.find('"', first) - first);
}


std::string spotifyUser::getUserTopItems(std::string type, std::string time_range, int limit, int offset) {
    //https://developer.spotify.com/console/get-current-user-top-artists-and-tracks/

    std::string validTypes = "artists tracks";
    std::string timeRanges = "long_term medium_term short_term";

    if (utility::isLimitsAndOffsetInvalid(limit, offset)) {
        spotifyLogToFile(__class__ + "::" + std::string(__func__) + "->Invalid limit/offset.\nLimit:" + std::to_string(limit) + "\nOffset: " + std::to_string(offset));
        return "invalid limit/offset";
    }else if (validTypes.find(type) == std::string::npos) {
        spotifyLogToFile(__class__+"::"+std::string(__func__) + "->Invalid type\ntype:" + type);
        return "invalid type";
    }else if (timeRanges.find(time_range) == std::string::npos) {
        spotifyLogToFile(__class__ + "::" + std::string(__func__) + "->Invalid time_range\ntime_range:" + time_range);
        return "invalid time_range";
    }

    //user-top-read
    std::string url = "https://api.spotify.com/v1/me/top/" + type
        + "?time_range=" + time_range
        + "&limit=" + std::to_string(limit)
        + "&offset=" + std::to_string(offset);

    std::string readBuffer = performCURLGET(url, spotifyAuthenticityToken);

    return utility::errorChecking(readBuffer, __class__, __func__);
}
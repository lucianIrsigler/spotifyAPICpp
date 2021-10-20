#include "spotifyUser.h"

/*
    Performs a cURL request for user data
    @returns readBuffer->User data in JSON form
*/
std::string spotifyUser::getUserInfo() {

    //acquires user data and stores in variable readBuffer
    std::string readBuffer = utility::performCURLGET("https://api.spotify.com/v1/me", spotifyAuthenticityToken);

    //checks readBuffer and returns right value
    return utility::errorChecking(readBuffer, __class__, __func__);
}

/*
    Performs a cURL request for the user's display name
    @returns userInfo->user's display name
*/
std::string spotifyUser::getDisplayName() {
    std::string userInfo = getUserInfo();
    std::cout << userInfo << std::endl;
    return userInfo.substr(22, userInfo.find('"', 22) - 22);
}

/*
    Performs a cURL request for the user's URL
    @returns userInfo->user's URL
*/
std::string spotifyUser::getUserURL() {
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"spotify\"") + 13;
    return userInfo.substr(first, userInfo.find('"', first) - first);
}

/*
    Performs a cURL request for the user's followers amount
    @returns followers->number of follows the user has
*/
int spotifyUser::getUserFollowers() {
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"total\"") + 10;
    std::string followers = userInfo.substr(first, userInfo.find('}', first) - first);
    return std::stoi(followers);
}

/*
    Performs a cURL request for the user's ID
    @returns userInfo->user's ID
*/
std::string spotifyUser::getUserID() {
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"id\"") + 8;
    return userInfo.substr(first, userInfo.find('"', first) - first);
}

/*
    Performs a cURL request for the user's profile picture source
    @returns userInfo->user's profile picture source
*/
std::string spotifyUser::getUserProfilePictureURL() {
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"url\"") + 9;
    return userInfo.substr(first, userInfo.find('"', first) - first);
}

/*
    Performs a cURL request for the user's type
    @returns userInfo->user's type
*/
std::string spotifyUser::getUserType() {
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"type\"") + 10;
    return userInfo.substr(first, userInfo.find('"', first) - first);
}

/*
    Performs a cURL request for the user's URI
    @returns userInfo->user's URI
*/
std::string spotifyUser::getUserURI() {
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"uri\"") + 9;
    return userInfo.substr(first, userInfo.find('"', first) - first);
}
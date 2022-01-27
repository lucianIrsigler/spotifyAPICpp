#pragma once
#include <memory>
#include "spotifyClientInfo.h"
#include "curl/curl.h"
#include "HTTPrequests.h"
#include "base64.h"
#include "spotifySearch.h"
#include "tokenFileMethods.h"


inline bool isAuthTokenExpired(std::string token) {
    return (searchSpotify("", "", token) == "The access token expired");
}

inline void autoRefreshTokenRawPointer(spotifyClientInfo* clientInfo);

inline void autoRefreshTokenUniquePointer(std::unique_ptr<spotifyClientInfo>& clientInfo);

inline void refreshTokenUniquePointer(std::unique_ptr<spotifyClientInfo>& clientInfo);

inline void refreshTokenRawPointer(spotifyClientInfo* clientInfo);


inline void autoRefreshTokenRawPointer(spotifyClientInfo* clientInfo) {
    if (isAuthTokenExpired(clientInfo->_authenticityToken) == 1) {
        refreshTokenRawPointer(clientInfo);
    }
}

inline void autoRefreshTokenUniquePointer(std::unique_ptr<spotifyClientInfo>& clientInfo) {
    if (isAuthTokenExpired(clientInfo->_authenticityToken) == 1) {
        refreshTokenUniquePointer(clientInfo);
    }
}

inline void refreshTokenUniquePointer(std::unique_ptr<spotifyClientInfo>& clientInfo) {

    //Creating the POST data for the OAuth2 token request
    std::string postData = "&grant_type=refresh_token&refresh_token=" + clientInfo->_refreshToken;

    //Creating the headers
    struct curl_slist* list = NULL;

    //The client ID and client secret needs to be in the form:
    //  client ID:client secret
    //and encoded in base64

    list = curl_slist_append(list, ("Authorization: Basic " + base64_encode(clientInfo->_spotifyClientID + ":" + clientInfo->_spotifyClientSecret)).c_str());

    //Performs POST request and saves the resulting token JSON in readBuffer
    std::string readBuffer = performCURLPOST("https://accounts.spotify.com/api/token", postData, list);

    //Offset to the start of the access token code in readBuffer
    int first = 17;

    //Sets the class's Token as the readBuffer's access token
    clientInfo->_authenticityToken = readBuffer.substr(first, readBuffer.find("token_type") - first - 3);

    writeTokensToFile(clientInfo->_authenticityToken, clientInfo->_refreshToken);
}

inline void refreshTokenRawPointer(spotifyClientInfo* clientInfo) {

    //Creating the POST data for the OAuth2 token request
    std::string postData = "&grant_type=refresh_token&refresh_token=" + clientInfo->_refreshToken;

    //Creating the headers
    struct curl_slist* list = NULL;

    //The client ID and client secret needs to be in the form:
    //  client ID:client secret
    //and encoded in base64

    list = curl_slist_append(list, ("Authorization: Basic " + base64_encode(clientInfo->_spotifyClientID + ":" + clientInfo->_spotifyClientSecret)).c_str());

    //Performs POST request and saves the resulting token JSON in readBuffer
    std::string readBuffer = performCURLPOST("https://accounts.spotify.com/api/token", postData, list);

    //Offset to the start of the access token code in readBuffer
    int first = 17;

    //Sets the class's Token as the readBuffer's access token
    clientInfo->_authenticityToken = readBuffer.substr(first, readBuffer.find("token_type") - first - 3);

    writeTokensToFile(clientInfo);
}

inline void refreshTokenData(std::string& refreshToken,std::string& ClientID,std::string& ClientSecret,std::string& authenticityToken) {

    //Creating the POST data for the OAuth2 token request
    std::string postData = "&grant_type=refresh_token&refresh_token=" + refreshToken;

    //Creating the headers
    struct curl_slist* list = NULL;

    //The client ID and client secret needs to be in the form:
    //  client ID:client secret
    //and encoded in base64

    list = curl_slist_append(list, ("Authorization: Basic " + base64_encode(ClientID + ":" + ClientSecret)).c_str());

    //Performs POST request and saves the resulting token JSON in readBuffer
    std::string readBuffer = performCURLPOST("https://accounts.spotify.com/api/token", postData, list);

    //Offset to the start of the access token code in readBuffer
    int first = 17;

    //Sets the class's Token as the readBuffer's access token
    authenticityToken = readBuffer.substr(first, readBuffer.find("token_type") - first - 3);

    writeTokensToFile(authenticityToken, refreshToken);
}
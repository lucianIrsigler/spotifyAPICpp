#include "pch.h"

template<typename T>
inline T refreshToken(T& clientInfo) {
    //Creating the POST data for the OAuth2 token request
    std::string postData = "&grant_type=refresh_token&refresh_token=" + clientInfo->_refreshToken;

    //Creating the headers
    struct curl_slist* list = NULL;

    //The client ID and client secret needs to be in the form:
    //  client ID:client secret
    //and encoded in spotify64

    list = curl_slist_append(list, ("Authorization: Basic "
        + spotify64_encode(clientInfo->_spotifyClientID + ":" + clientInfo->_spotifyClientSecret)).c_str());

    //Performs POST request and saves the resulting token JSON in readBuffer
    std::string readBuffer = performCURLPOST("https://accounts.spotify.com/api/token", postData, list);

    //Offset to the start of the access token code in readBuffer
    int first = 17;

    //Sets the class's Token as the readBuffer's access token
    clientInfo->_authenticityToken = readBuffer.substr(first, readBuffer.find("token_type") - first - 3);

    writeTokensToFile(clientInfo->_authenticityToken, clientInfo->_refreshToken);
}

/*inline bool isAuthTokenExpired(std::string token) {
    return (searchSpotify("", "", token) == "The access token expired");
}*/


void refreshTokenData(std::string& refreshToken, std::string& ClientID,
    std::string& ClientSecret, std::string& authenticityToken) {

    if (refreshToken == "" || ClientID == "" || ClientSecret == "" || authenticityToken == "") {
        spotifyLogToFile("refreshTokenData->a field is empty");
    }
    //Creating the POST data for the OAuth2 token request
    std::string postData = "&grant_type=refresh_token&refresh_token=" + refreshToken;

    //Creating the headers
    struct curl_slist* list = NULL;

    //The client ID and client secret needs to be in the form:
    //  client ID:client secret
    //  and encoded in spotify64

    list = curl_slist_append(list, ("Authorization: Basic "
        + spotify64_encode(ClientID + ":" + ClientSecret)).c_str());

    //Performs POST request and saves the resulting token JSON in readBuffer
    std::string readBuffer = performCURLPOST("https://accounts.spotify.com/api/token", postData, list);

    //Offset to the start of the access token code in readBuffer
    int first = 17;

    //Sets the class's Token as the readBuffer's access token
    authenticityToken = readBuffer.substr(first, readBuffer.find("token_type") - first - 3);

    tokenMethods::writeTokensToFile(authenticityToken, refreshToken);
}
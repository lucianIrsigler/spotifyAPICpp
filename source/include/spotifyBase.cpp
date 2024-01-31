#include "pch.h"
#include "spotifyBase.h"
#include <string>

void SpotifyBase::authorize(std::string scopes) {

    std::string requestURL;

    try {
        requestURL = auth::generateAuthenticationURL(scopes, clientID, redirectURI);
    }
    catch (spotifyException e) {
        spotifyLogToFile("Invalid scopes:" + scopes);
        return;
    }

    std::string url = auth::executeSearchWebBrowser(requestURL);

    std::string tempToken = auth::getTempToken(url);

    std::string readBuffer = auth::tradeForAuthenticationToken(clientID, clientSecret, tempToken);

    auth::setTokensValues(authenticityToken, refreshToken, readBuffer, scopes);

}

/*
    Trades refresh token for another OAuth2 token. Refresh token can be use indefinetly
*/
void SpotifyBase::refreshAuthToken() {
    refreshTokenData(refreshToken, clientID, clientSecret, authenticityToken);
}


void SpotifyBase::getTokenValuesFromFile() {
    authenticityToken = tokenMethods::getAuthTokenFromFile();
    refreshToken = tokenMethods::getRefreshTokenFromFile();
}


bool SpotifyBase::checkIfTokenExpired() {
    //If token/refresh files have valid length tokens
    if (tokenMethods::checkAuthTokenLength && tokenMethods::checkRefreshTokenLength()) {
        std::string token = tokenMethods::getAuthTokenFromFile();

        // v1/me can be accessed regardless of scope
        std::string readBuffer = performCURLGET("https://api.spotify.com/v1/me", token);
        return readBuffer.find("error") != std::string::npos;
    }

    return true;
}

bool SpotifyBase::checkIfAuthTokenExpired() {
    std::string readBuffer = performCURLGET("https://api.spotify.com/v1/me", authenticityToken);
    return readBuffer.find("error") != std::string::npos;
}
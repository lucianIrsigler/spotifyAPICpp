#include "base.h"


void base::authorize(std::string scopes) {

    std::string requestURL;

    try {
        requestURL = generateAuthenticationURL(scopes, clientID, redirectURI);
    }
    catch (spotifyException& e) {
        spotifyLogToFile("Invalid scopes:" + scopes);
        return;
    }

    std::string url = executeSearchWebBrowser(requestURL);

    std::string tempToken = getTempToken(url);

    std::string readBuffer = tradeForAuthenticationToken(clientID, clientSecret, tempToken);

    setTokensValues(authenticityToken, refreshTokens, readBuffer, scopes);
}


/*
    Trades refresh token for another OAuth2 token. Refresh token can be use indefinetly
*/
void base::refreshToken(){
    refreshTokenData(refreshTokens, clientID, clientSecret, authenticityToken);
}


void base::updateTokensValues() {
    authenticityToken = clientInfo->_authenticityToken;
    refreshTokens = clientInfo->_refreshToken;
}
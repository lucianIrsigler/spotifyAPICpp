#pragma once
#include "tokenFileMethods.h"

class SpotifyBase
{
public:
    SpotifyBase() {}
    SpotifyBase(std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect)
        :authenticityToken(authToken),
        clientID(userspotifyClientID),
        clientSecret(userClientSecret),
        redirectURI(userRedirect) {
    }

    /*
            Sends a request to acquire a valid spotify token and refresh token
            @param scopes->Scopes of the token
    */
    void authorize(std::string scopes = "");

    void refreshAuthToken();

    void getTokenValuesFromFile();

    /*
    Method to check if token has expired
    */
    bool checkIfTokenExpired();

    //check if auth token expired
    bool checkIfAuthTokenExpired();

    std::string authenticityToken;
    std::string refreshToken;

private:
    std::string clientID;
    std::string clientSecret;
    std::string redirectURI;
};

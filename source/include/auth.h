#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <ShellAPI.h>
#include "HTTPrequests.h"
#include "spotifyexception.h"
#include "misc.h"
#include "base64.h"
#include "scopes.h"
#include "logging.h"
#include "tokenFileMethods.h"


namespace auth {
    inline const std::string generateAuthenticationURL(std::string scopes, std::string& spotifyClientID,
        std::string& spotifyRedirectURI);

    inline const std::string executeSearchWebBrowser(std::string requestedURL);

    inline const std::string getTempToken(std::string authURL);

    std::string tradeForAuthenticationToken(std::string& spotifyClientID, std::string& spotifyClientSecret,
        std::string& tempToken);

    inline void setTokensValues(std::string& authenticityToken, std::string& spotifyRefreshToken,
        std::string& readBuffer, std::string& scopes);


    inline const std::string generateAuthenticationURL(std::string scopes, std::string& spotifyClientID, std::string& spotifyRedirectURI) {
        if (!isValidScopes(scopes)) {
            throw spotifyException("Invalid scopes");
        }

        //A state is a random combination of characters that provides additional protection against threats like
       //cross-site request forgery.
        std::string state = generateRandomText(8);

        //Creates the url
        std::string requestURL = "https://accounts.spotify.com/authorize?client_id=" + spotifyClientID
            + "&response_type=code"
            + "&redirect_uri=" + spotifyRedirectURI
            + "&state=" + state
            + "&scope=" + scopes;

        return requestURL;
    }

    inline const std::string executeSearchWebBrowser(std::string requestedURL) {

        //Converts to LPCWSTR so requestURL can be used in the shell
        std::wstring temp = std::wstring(requestedURL.begin(), requestedURL.end());
        LPCWSTR search = temp.c_str();

        //std::cout << requestedURL << std::endl;
        //Opens the shell to open the browser and redirect to the requestURL
        ShellExecute(0, 0, search, 0, 0, SW_SHOW);

        //string to hold redirect url
        std::string authenticationURL;
        std::cin >> authenticationURL;

        return authenticationURL;
    }

    inline const std::string getTempToken(std::string authURL) {
        int32_t start = authURL.find("code");
        int32_t end = authURL.find("&state");

        //The code is stored in the variable tempToken
        std::string tempToken = authURL.substr(start + 5, end - start - 5);

        return tempToken;
    }

    inline std::string tradeForAuthenticationToken(std::string& spotifyClientID, std::string& spotifyClientSecret, std::string& tempToken) {
        printf("Trading code for OAuth2 token...\n");

        //Creating the POST data for the OAuth2 token request
        std::string postData = "client_id=" + spotifyClientID
            + "&grant_type=authorization_code"
            + "&code=" + tempToken
            + "&redirect_uri=https://www.google.com";

        struct curl_slist* list = NULL;

        //The client ID and client secret needs to be in the form:
        //  client ID:client secret
        //and encoded in spotify64
        list = curl_slist_append(list, ("Authorization: Basic " + spotify64_encode(spotifyClientID + ":" + spotifyClientSecret)).c_str());

        //Performs POST request and saves the resulting token JSON in readBuffer

        std::string readBuffer = performCURLPOST("https://accounts.spotify.com/api/token", postData, list);

        return readBuffer;
    }

    inline void setTokensValues(std::string& authenticityToken, std::string& spotifyRefreshToken, std::string& readBuffer, std::string& scopes) {
        //Offset to the start of the access token code in readBuffer
        int first = 17;

        //Sets the class's Token as the readBuffer's access token
        authenticityToken = readBuffer.substr(first, readBuffer.find("token_type") - first - 3);

        spotifyLogToFile("AUTH TOKEN ACQUIRED:" + authenticityToken + "\nScopes:" + scopes);

        int refreshFirst = readBuffer.find("refresh_token") + 16;

        //Sets the class's refresh token
        spotifyRefreshToken = readBuffer.substr(refreshFirst, readBuffer.find('"', refreshFirst) - refreshFirst);

        tokenMethods::writeTokensToFile(authenticityToken, spotifyRefreshToken);
    }
}

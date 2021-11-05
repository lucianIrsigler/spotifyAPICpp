#include "base.h"

void base::basicauthorize(std::string scopes) {

    //Checks if scopes are valid
    if (!validateScopes(scopes)) {
        spotifyLogToFile("Invalid scopes:"+ _className+"\nscopes:"+scopes);
        return;
    }

    //A state is a random combination of characters that provides additional protection against threats like
    //cross-site request forgery.
    std::string state = utility::generateRandomText(8);

    //Creates the url
    std::string requestURL = "https://accounts.spotify.com/authorize?client_id=" + spotifyClientID
        + "&response_type=code"
        + "&redirect_uri=" + spotifyRedirectURI
        + "&state=" + state
        + "&scope=" + scopes;

    
    //Converts to LPCWSTR so requestURL can be used in the shell
    std::wstring temp = std::wstring(requestURL.begin(), requestURL.end());
    LPCWSTR search = temp.c_str();


    //Opens the shell to open the browser and redirect to the requestURL
    ShellExecute(0, 0, search, 0, 0, SW_SHOW);

    //string to hold redirect url
    std::string url;
    std::cin >> url;

    //Searches the string to find the code

    int32_t start = url.find("code");
    int32_t end = url.find("&state");

    //The code is stored in the variable tempToken
    std::string tempToken = url.substr(start + 5, end - start - 5);

    std::cout << "Trading code for OAuth2 token..." << std::endl;

    //Creating the POST data for the OAuth2 token request
    std::string postData = "client_id=" + spotifyClientID
        + "&grant_type=authorization_code"
        + "&code=" + tempToken
        + "&redirect_uri=https://www.google.com";

    //Creating the headers
    struct curl_slist* list = NULL;

    //The client ID and client secret needs to be in the form:
    //  client ID:client secret
    //and encoded in base64
    list = curl_slist_append(list, ("Authorization: Basic " + base64_encode(spotifyClientID + ":" + spotifyClientSecret)).c_str());

    //Performs POST request and saves the resulting token JSON in readBuffer

    std::string readBuffer = performCURLPOST("https://accounts.spotify.com/api/token", postData, list);

    std::cout << "\n\n" << readBuffer << "\n\n" << std::endl;
    //std::cout << readBuffer << std::endl;

    //Offset to the start of the access token code in readBuffer
    int first = 17;

    //Sets the class's Token as the readBuffer's access token
    spotifyAuthenticityToken = readBuffer.substr(first, readBuffer.find("token_type") - first - 3);

    spotifyLogToFile("AUTH TOKEN ACQUIRED:" + spotifyAuthenticityToken + "\nScopes:" + scopes);
    //Finds the first index of the refresh token
    //The '16' is the offset from the first index of readBuffer.find("refresh_token")
    int refreshFirst = readBuffer.find("refresh_token") + 16;

    //Sets the class's refresh token
    spotifyRefreshToken = readBuffer.substr(refreshFirst, readBuffer.find('"', refreshFirst) - refreshFirst);


}


std::vector<std::string> base::spotifyScopes() {
    std::vector<std::string>availableScopes = {
        "ugc-image-upload",
        "playlist-modify-private",
        "playlist-read-private",
        "user-read-private",
        "user-read-playback-state",
        "user-library-modify",
        "user-read-playback-position",
        "app-remote-control",
        "user-read-recently-played",
        "user-modify-playback-state",
        "user-read-email",
        "user-follow-modify",
        "playlist-modify-public",
        "user-follow-read",
        "user-read-currently-playing",
        "playlist-read-collaborative",
        "user-library-read",
        "streaming",
        "user-top-read"
    };

    return availableScopes;
}

/*

*/
bool base::isValidScopes(std::string scope) {
    std::vector<std::string>scopes = spotifyScopes();
    if (std::find(scopes.begin(), scopes.end(), scope) != scopes.end()) {
        return true;
    }
    return false;
}


/*
    Validates inputted scopes.
    @param userScopes- scopes to validate(scopes must be seperated by a space)
*/
bool base::validateScopes(std::string userScopes) {

    if (userScopes == "") {
        return true;
    }

    std::vector<std::string>scopes = spotifyScopes();

    int first = 0;

    while (userScopes.find(" ", first) != std::string::npos) {
        std::string message = userScopes.substr(first, userScopes.find(' ', first + 1) - first);

        message.erase(remove_if(message.begin(), message.end(), isspace), message.end());

        if (std::find(scopes.begin(), scopes.end(), message) != scopes.end()) {
            /* v contains x */
            first = userScopes.find(' ', first + 1);
        }
        else {
            /* v does not contain x */
            return false;
        }
    }

    return true;
}

/*
    Trades refresh token for another OAuth2 token. Upon the exchange- the API does not provide another refresh token
*/
void base::refreshToken() {
    //Creating the POST data for the OAuth2 token request

    std::string postData = "&grant_type=refresh_token&refresh_token=" + spotifyRefreshToken;

    //Creating the headers
    struct curl_slist* list = NULL;

    //The client ID and client secret needs to be in the form:
    //  client ID:client secret
    //and encoded in base64
    list = curl_slist_append(list, ("Authorization: Basic " + base64_encode(spotifyClientID + ":" + spotifyClientSecret)).c_str());

    //Performs POST request and saves the resulting token JSON in readBuffer
    std::string readBuffer = performCURLPOST("https://accounts.spotify.com/api/token", postData, list);

    //std::cout << readBuffer << std::endl;
    // 
    //Offset to the start of the access token code in readBuffer
    int first = 17;

    //Sets the class's Token as the readBuffer's access token
    spotifyAuthenticityToken = readBuffer.substr(first, readBuffer.find("token_type") - first - 3);

    /*
    //Finds the first index of the refresh token
    //The '16' is the offset from the first index of readBuffer.find("refresh_token")
    int refreshFirst = readBuffer.find("refresh_token") + 16;

    //Sets the class's refresh token as the readBuffer's refresh token
    spotifyRefreshToken = readBuffer.substr(refreshFirst, readBuffer.find('"', refreshFirst) - refreshFirst);*/
    spotifyRefreshToken = "";
}

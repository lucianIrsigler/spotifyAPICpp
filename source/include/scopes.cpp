#include "scopes.h"

std::vector<std::string> spotifyScopes() {
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


bool isValidScope(std::string scope) {
    std::vector<std::string> fullScope = spotifyScopes();
    return std::find(fullScope.begin(), fullScope.end(), scope) != fullScope.end();
}


/*
    Validates inputted scopes.
    @param userScopes- scopes to validate(scopes must be seperated by a space)
*/
bool isValidScopes(std::string scopesToCheck) {

    if (scopesToCheck == "") {
        return true;
    }

    std::vector<std::string>scopes = spotifyScopes();

    int first = 0;

    while (scopesToCheck.find(" ", first) != std::string::npos) {
        //gets substr
        std::string message = scopesToCheck.substr(first, scopesToCheck.find(' ', first + 1) - first);

        //removes space
        message.erase(remove_if(message.begin(), message.end(), isspace), message.end());

        //checks if scope is valid
        if (std::find(scopes.begin(), scopes.end(), message) != scopes.end()) {
            /* v contains x */
            first = scopesToCheck.find(' ', first + 1);
        }
        else {
            /* v does not contain x
            Scopes are invalid thus*/
            return false;
        }
    }

    return true;
}

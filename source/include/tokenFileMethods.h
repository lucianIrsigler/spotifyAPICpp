#pragma once
#include <fstream>
#include "spotifyClientInfo.h"

inline void writeTokensToFile(std::string authToken, std::string refreshToken);

inline void writeTokensToFile(spotifyClientInfo* clientInfo);

inline bool checkIfAuthTokenExists();

inline std::string getAuthTokenFromFile();

inline bool checkIfRefreshTokenExists();

inline std::string getRefreshTokenFromFile();


inline void writeTokensToFile(spotifyClientInfo* clientInfo)
{
    std::ofstream file;

    file.open("_token.txt");
    file << clientInfo->_authenticityToken;
    file.close();

    file.open("_refresh.txt");
    file << clientInfo->_refreshToken;
    file.close();
}

inline void writeTokensToFile(std::string authToken, std::string refreshToken) {
    std::ofstream file;

    file.open("_token.txt");
    file << authToken;
    file.close();

    file.open("_refresh.txt");
    file << refreshToken;
    file.close();
}


inline bool checkIfAuthTokenExists() {
    std::ifstream file("_token.txt");
    std::string line;

    if (file) {
        std::getline(file, line);
        if (line != "") {
            return true;
        }
    }

    return false;
}

inline std::string getAuthTokenFromFile()
{
    std::ifstream file("_token.txt");
    std::string line;

    if (file) {
        std::getline(file, line);
        return line;
    }
}

inline bool checkIfRefreshTokenExists() {
    std::ifstream file("_refresh.txt");
    std::string line;

    if (file) {
        std::getline(file, line);
        return (line != "");
    }
    return false;
}


inline std::string getRefreshTokenFromFile()
{
    std::ifstream file("_refresh.txt");
    std::string line = "";

    if (file) {
        std::getline(file, line);
        return line;
    }
}

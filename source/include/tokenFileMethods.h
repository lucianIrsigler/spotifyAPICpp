#pragma once
#include <fstream>
#include <string>


namespace tokenMethods {
    /**/
    inline void writeTokensToFile(std::string authToken, std::string refreshToken);

    /**/
    inline bool checkIfAuthTokenExists();

    /**/
    inline std::string getAuthTokenFromFile();

    /**/
    inline bool checkAuthTokenLength();

    /**/
    inline bool checkIfRefreshTokenExists();

    /**/
    inline std::string getRefreshTokenFromFile();

    /**/
    inline bool checkRefreshTokenLength();
    

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


    inline std::string getAuthTokenFromFile() {
        std::ifstream file("_token.txt");
        std::string line;

        if (file) {
            std::getline(file, line);
            return line;
        }
        else {
            return "";
        }
    }

    inline bool checkAuthTokenLength() {
        int authTokenMinLength = 167;
        std::ifstream file("_token.txt");
        std::string line;

        if (file) {
            std::getline(file, line);
            if (line.length() + 1 > size_t(authTokenMinLength) || line.length() + 1 == authTokenMinLength) {
                return true;
            }
        }

        return false;
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


    inline std::string getRefreshTokenFromFile() {
        std::ifstream file("_refresh.txt");
        std::string line = "";

        if (file) {
            std::getline(file, line);
            return line;
        }
        else {
            return "REFRESHTOKEN";
        }
    }

    inline bool checkRefreshTokenLength() {
        int refreshTokenMinLength = 100;
        std::ifstream file("_refresh.txt");
        std::string line;

        if (file) {
            std::getline(file, line);
            if (line.length() + 1 > size_t(refreshTokenMinLength) || line.length() + 1 == refreshTokenMinLength) {
                return true;
            }
        }

        return false;
    }
}
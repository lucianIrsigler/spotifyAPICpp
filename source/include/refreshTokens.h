#pragma once
template<typename T>
inline T refreshToken(T& clientInfo);


void refreshTokenData(std::string& refreshToken, std::string& ClientID,
    std::string& ClientSecret, std::string& authenticityToken);
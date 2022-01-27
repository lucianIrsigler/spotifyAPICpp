#pragma once
#include <string>

/*
Struct used to hold information about the application
*/
struct spotifyClientInfo {
	spotifyClientInfo(
		std::string token,
		std::string refreshToken,
		std::string clientID,
		std::string clientSecret,
		std::string clientRedirectURI) :
		_authenticityToken{ token }, _refreshToken{ refreshToken }, _spotifyClientID{ clientID },
		_spotifyClientSecret{ clientSecret }, _spotifyRedirectURI{ clientRedirectURI } {};

	spotifyClientInfo() {};

		std::string _authenticityToken;
		std::string _refreshToken;
		std::string _spotifyClientID;
		std::string _spotifyClientSecret;
		std::string _spotifyRedirectURI;
};
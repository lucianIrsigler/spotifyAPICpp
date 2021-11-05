#pragma once
#include <string>

/*
Struct used to hold information about the application
*/
struct spotifyInfo {
	std::string _spotifyAuthenticityToken;
	std::string _spotifyClientID;
	std::string _spotifyClientSecret;
	std::string _spotifyRedirectURI;

	spotifyInfo(std::string token, std::string clientID, std::string clientSecret, std::string clientRedirectURI) :
		_spotifyAuthenticityToken(token), _spotifyClientID(clientID),
		_spotifyClientSecret(clientSecret), _spotifyRedirectURI(clientRedirectURI) {};
	spotifyInfo(){}
};

#pragma once
#include <string>
#include <vector>
#include "base64.h"
#include "utility.h"
#include "spotifylogging.h"
#define __class__ std::string(typeid(*this).name())

class base
{
public:
	base() {}
	base(std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect)
		:spotifyAuthenticityToken(authToken),
		spotifyClientID(userspotifyClientID),
		spotifyClientSecret(userClientSecret),
		spotifyRedirectURI(userRedirect)
	{
	}

	virtual void basicauthorize(std::string scopes = "");

	//Scopes

	std::vector<std::string> spotifyScopes();
	bool isValidScopes(std::string scope);
	bool validateScopes(std::string userScopes);

	//Acquire another token

	void refreshToken();

	std::string spotifyClassScopes;
	std::string spotifyAuthenticityToken;
	std::string spotifyRefreshToken;

private:

	std::string spotifyClientID;
	std::string spotifyClientSecret;
	std::string spotifyRedirectURI;
};


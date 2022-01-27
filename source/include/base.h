#pragma once
#include <iostream>
#include "base64.h"
#include "HTTPrequests.h"
#include "tokenFileMethods.h"
#include "errorhandling.h"
#include "auth.h"
#include "refreshTokens.h"

using std::cin;

class base
{
public:
	base() {}
	base(std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect)
		:authenticityToken(authToken),
		clientID(userspotifyClientID),
		clientSecret(userClientSecret),
		redirectURI(userRedirect)
	{
	}

	base(spotifyClientInfo * info) {
		authenticityToken = info->_authenticityToken;
		refreshTokens = info->_refreshToken;
		clientID = info->_spotifyClientID;
		clientSecret = info->_spotifyClientSecret;
		redirectURI = info->_spotifyRedirectURI;
		clientInfo = info;
	}


	base(base&& spotifyClass) = delete;
	base(base& spotifyClass) = delete;
	base(const base& spotifyClass) = delete;
	
	/*
		Sends a request to acquire a valid spotify token and refresh token
		@param scopes->Scopes of the token
	*/
	void authorize(std::string scopes = "");

	void refreshToken();

	/*
		Updates authenticityToken and spotifyRefreshToken
		to the values of clientInfo->_authenticityToken and clientInfo->_refreshToken
	*/
	void updateTokensValues();

	std::string authenticityToken;
	std::string refreshTokens;
	spotifyClientInfo* clientInfo = nullptr;

private:
	std::string clientID;
	std::string clientSecret;
	std::string redirectURI;
};


#pragma once
#include "base64.h"
#include "utility.h"
#include "HTTPrequests.h"
#include "spotifyInfoStruct.h"

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

	base(spotifyInfo * info) {
		spotifyAuthenticityToken = info->_spotifyAuthenticityToken;
		spotifyClientID = info->_spotifyClientID;
		spotifyClientSecret = info->_spotifyClientSecret;
		spotifyRedirectURI = info->_spotifyRedirectURI;
	}


	base(base&& spotifyClass) = delete;
	base(base& spotifyClass) = delete;
	base(const base& spotifyClass) = delete;

	/*
		Sends a request to acquire a valid spotify token
		@param scopes->Scopes of the token
	*/
	void basicauthorize(std::string scopes = "");

	//Scopes

	/*
		A vector containing all valid spotify scopes
		@returns vector containing scopes
	*/
	std::vector<std::string> spotifyScopes();

	/*
		Checks if a scope is valid
		@scope->scope to check
		@returns whether scope is valid
	*/
	bool isValidScopes(std::string scope);

	/*
		Checks if several scopes is valid(space seperated)
		@scope->scopes to check(Example: "scope1 scope2 scope3"
		@returns whether scope string is valid
	*/
	bool validateScopes(std::string userScopes);

	/*
		Uses the refresh token to acquire another token
	*/
	void refreshToken();

	std::string _className;
	std::string spotifyAuthenticityToken;
	std::string spotifyRefreshToken;

private:
	std::string spotifyClientID;
	std::string spotifyClientSecret;
	std::string spotifyRedirectURI;
};


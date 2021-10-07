#pragma once
#include <iostream>
#include <vector>
#include "sha256.h"
#include "base64.h"
#include "utility.h"
#include <algorithm>
#include <stdlib.h>

class Spotify
{
public:
	
	Spotify(std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect)
		:spotifyAuthenticityToken(authToken), 
		 spotifyClientID(userspotifyClientID),
		 spotifyClientSecret(userClientSecret),
		 spotifyRedirectURI(userRedirect)
	{}
	~Spotify() {};

	//deletes copy construtors
	Spotify(Spotify& spotify) = delete; 
	Spotify(const Spotify& spotify) = delete;

	//rvalue
	Spotify(Spotify&& other) noexcept {
		printf("Moved\n");
		spotifyAuthenticityToken = other.spotifyAuthenticityToken;
		spotifyClientID = other.spotifyClientID;
		spotifyClientSecret = other.spotifyClientSecret;
		spotifyRedirectURI = other.spotifyRedirectURI;


		other.spotifyAuthenticityToken = nullptr;
		other.spotifyClientID = nullptr;
		other.spotifyClientSecret=nullptr;
		other.spotifyRedirectURI = nullptr;
	};

	//rvalue move
	Spotify& operator=(Spotify&& other) noexcept {
		spotifyAuthenticityToken = other.spotifyAuthenticityToken;
		spotifyClientID = other.spotifyClientID;
		spotifyClientSecret = other.spotifyClientSecret;
		spotifyRedirectURI = other.spotifyRedirectURI;

		return *this;
	}
	//Authorizing
	void basicauthorize(std::string scopes);
	void authorizePCKE();

	//User info
	std::string getUserInfo();
	std::string getDisplayName();
	std::string getUserURL();
	int getUserFollowers();
	std::string getUserID();
	std::string getUserProfilePictureURL();
	std::string getUserType();
	std::string getUserURI();

	//PLAYER
	std::string getUserPlaylists(int limit);
	std::string getUserCurrentPlaying();

	//Getters
	std::string getToken();
	std::string getClientID();
	std::string getClientSecret();

	//Setters
	void setToken(std::string userToken);
	void setClientID(std::string userspotifyClientID);
	void setClientSecret(std::string userspotifyClientSecret);

	//Scopes
	std::vector<std::string> spotifyScopes();
	bool validateScopes(std::string userScopes);

private:
	std::string spotifyAuthenticityToken;
	std::string spotifyClientID;
	std::string spotifyClientSecret;
	std::string spotifyRedirectURI;
	std::string spotifyRefreshToken;
};


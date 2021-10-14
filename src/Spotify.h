/**
	Spotify.h
	Purpose: Creates the class for interacting with the Spotify API

	@author Lucian Irsigler
	@version 1.0 14/10/2021
*/

#pragma once
#include <iostream>
#include <vector>
#include "sha256.h"
#include "base64.h"
#include "utility.h"
#include <algorithm>
#include <stdlib.h>
#include "spotifyexception.h"

class Spotify
{
public:
	Spotify(){}
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

	//Playlist

	std::string getSearchedUserPlaylists(std::string userID, int limit, int offset);
	std::string getUserPlaylists(int limit = 20, int offset = 0);
	std::string getPlaylist(std::string playlistID, std::string market, std::string fields);
	std::string getPlaylistCover(std::string playlistID);
	std::string getPlaylistItems(std::string playlistID, std::string market, std::string fields, int limit = 20, int offset = 0);
	void createPlaylist(std::string userID, std::string name, std::string description, bool isPublic);
	void addItemToPlaylist(std::string playlistID, std::string URI, int position,std::vector<std::string> URIS);
	void deleteItemFromPlaylist(std::string playlistID, std::vector<std::string> URIS);
	void updatePlaylistItems(std::string playlistID, std::string URIs, std::string requestBody);
	void changePlaylistDetails(std::string playlistID,std::string name, std::string description, bool isPublic);


	//Player

	std::string getUserRecentPlaying(int limit);
	std::string getUserPlaybackState();
	void transferUserPlayback();
	std::string getAvialableDevices();
	std::string getUserCurrentPlaying();
	void resumeUserPlayback();
	void pauseUserPlayback(std::string deviceID);
	void skipToNextTrack(std::string deviceID);
	void skipToPreviousTrack(std::string deviceID);
	void seekToPositionCurrentTrack();
	void setRepeatOnPlayback(std::string state,std::string deviceID);
	void setVolumeOnPlayback(int volume, std::string deviceID);
	void toggleShuffleOnPlayback(bool shuffle, std::string deviceID);
	void addSongToUserQueue(std::string URI, std::string deviceID);


	//Scopes

	std::vector<std::string> spotifyScopes();
	bool isValidScopes(std::string scope);
	bool validateScopes(std::string userScopes);

	//Acquire another token

	void refreshToken();

	//utility
	bool isLimitsAndOffsetInvalid(int limit, int offset);
	void checkConditions(std::string& request);

	std::string spotifyClassScopes;
	std::string spotifyAuthenticityToken;
	std::string spotifyRefreshToken;

private:
	std::string spotifyClientID;
	std::string spotifyClientSecret;
	std::string spotifyRedirectURI;
};
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
	std::string getUserPlaylists(int limit, int offset);
	std::string getPlaylist(std::string playlistID, std::string market, std::string fields);
	std::string getPlaylistCover(std::string playlistID);
	std::string getPlaylistItems(std::string playlistID, std::string market, std::string fields, int limit, int offset);
	void createPlaylist(std::string userID, std::string requestBody);
	void addItemToPlaylist(std::string playlistID, int position, std::string URI, std::string requestBody);
	void deleteItemFromPlaylist(std::string playlistID, std::string requestBody);
	void updatePlaylistItems(std::string playlistID, std::string URIs, std::string requestBody);
	void changePlaylistDetails(std::string playlistID, std::string requestBody);


	//Player

	std::string getUserRecentPlaying(int limit);
	std::string getUserPlaybackState();
	void transferUserPlayback();
	std::string getAvialableDevices();
	std::string getUserCurrentPlaying();
	void resumeUserPlayback();
	void pauseUserPlayback();
	void skipToNextTrack();
	void skipToPreviousTrack();
	void seekToPositionCurrentTrack();
	void setRepeatOnPlayback();
	void setVolumeOnPlayback();
	void toggleShuffleOnPlayback();
	void addSongToUserQueue(std::string URI, std::string deviceID);


	//Scopes

	std::vector<std::string> spotifyScopes();
	bool isValidScopes(std::string scope);
	bool validateScopes(std::string userScopes);

	//Acquire another token

	void refreshToken();

	//utility
	bool isLimitsAndOffsetInvalid(int limit, int offset);

	std::string spotifyClassScopes;
private:
	std::string spotifyAuthenticityToken;
	std::string spotifyClientID;
	std::string spotifyClientSecret;
	std::string spotifyRedirectURI;
	std::string spotifyRefreshToken;
};


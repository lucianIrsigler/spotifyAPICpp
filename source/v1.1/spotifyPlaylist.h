#pragma once
#include <iostream>
#include <vector>
#include "utility.h"
#include "base.h"
#include "json.h"

class spotifyPlaylist:public base
{
public:
	spotifyPlaylist() :base() {};
	spotifyPlaylist(
		std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect) :
		base(authToken, userspotifyClientID, userClientSecret, userRedirect) {
		spotifyLogToFile("Created:" + std::string(typeid(*this).name()));
	};

	//GET

	std::string getSearchedUserPlaylists(std::string userID, int limit=20, int offset=0);
	std::string getUserPlaylists(int limit = 20, int offset = 0);
	std::vector<std::string> getUserPlaylistsNames();
	std::string getPlaylist(std::string playlistID, std::string market, std::string fields);
	std::string getPlaylistCover(std::string playlistID);
	std::string getPlaylistItems(std::string playlistID, std::string market, std::string fields, int limit = 20, int offset = 0);
	
	//POST
	void createPlaylist(std::string userID, std::string name, std::string description, bool isPublic);
	void addItemToPlaylist(std::string playlistID, std::string URI, int position, std::vector<std::string> URIS);
	
	//DELETE
	void deleteItemFromPlaylist(std::string playlistID, std::vector<std::string> URIS);

	//PUT
	void updatePlaylistCover(std::string playlist);
	void updatePlaylistItems(std::string playlistID, std::string URIs, std::string requestBody);
	void changePlaylistDetails(std::string playlistID, std::string name, std::string description, bool isPublic = true);
};


#pragma once
#include <string>
#include "spotifyBase.h"

class spotifyPlaylist :public SpotifyBase
{
public:
	spotifyPlaylist();
	spotifyPlaylist(
		std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect);

	//GET

	/*
		Searches for a user and returns their playlists.Scopes:playlist-read-private playlist-read-collaborative
		Required scopes:playlist-read-private playlist-read-collaborative
		@param userID->userID to search for
		@param limit->number of playlists to return. Max is 50 and minimum 1
		@param offset->How many playlists to skip initially
		@returns User's playlist in JSON format
	*/
	std::string getSearchedUserPlaylists(std::string userID, int limit = 20, int offset = 0);

	/*
		Gets the user associated with the token's playlists.Scopes:playlist-read-private
		@param limit->number of playlists to get
		@param offset->number of playlists to skip initially
		@returns User's playlist in JSON format
	*/
	std::string getUserPlaylists(int limit = 20, int offset = 0);

	/**/
	//std::vector<spotifyPlaylistObject> getUserPlaylistsObjects();

	/*
		Gets a playlist.Scopes:NONE
		@param playlistID->playlistID to search for
		@param market-> market to search for
		@param fields->fields to search for
		@returns Playlist info

	*/
	std::string getPlaylist(std::string playlistID, std::string market, std::string fields);

	/*
		Retrieves the playlist display picture.Scopes:NONE
		@param playlistID->playlist to search for
		@returns url of the playlist cover
	*/
	std::string getPlaylistCover(std::string playlistID);


	/*
		Gets a playlist's songs.Scopes:playlist-read-public playlist-read-private
		@param playlistID->playlist to search for
		@param market->market of songs to find
		@param fields->fields to search for
		@param limit->number of songs to search for. Max is 50
		@param offset->How many playlists are skipped initially
		@returns JSON response with track information
	*/
	std::string getPlaylistItems(std::string playlistID, std::string market, std::string fields, int limit = 20, int offset = 0);

	//POST

	/*
		Creates a playlist.
		Required scopes:playlist-modify-public playlist-modify-private
		@param userID->User to create the playlist for
		@param name-> name of playlist
		@param description->Description of playlist
		@param isPublic->The playlist's public status
	*/
	void createPlaylist(std::string userID, std::string name, std::string description, bool isPublic);

	/*
		Adds a song to a playlist.Scopes:playlist-modify-public playlist-modify-private
		Required scopes:playlist-modify-public playlist-modify-private
		@param playlistID->playlist to search for
		@param URI->song to add. Leave empty if you are adding via the vector
		@param position->Position to add the songs into the Playlist
		@param URIS->songs to add
	*/
	void addItemToPlaylist(std::string playlistID, std::string URI, int position, std::vector<std::string> URIS);

	//DELETE

	/*
		Deletes a song to a playlist.Scopes:playlist-modify-public playlist-modify-private
		Required scopes:playlist-modify-public playlist-modify-private
		@param playlistID->playlist to search for
		@param URIS->songs to delete
	*/
	void deleteItemFromPlaylist(std::string playlistID, std::vector<std::string> URIS);

	//PUT


	void updatePlaylistCover(std::string playlist) {};

	/*
	*/
	void updatePlaylistItems(std::string playlistID, std::string URIs, std::string requestBody);

	/*
		Changes a playlist's details.
		Scopes:playlist-modify-public playlist-modify-private
		@param playlistID->ID of playlist to edit
		@param name-> new name to give the playlist
		@param description->New description for the playlist
		@param isPublic->Change whether the playlist can be displayed on the user's profile
	*/
	void changePlaylistDetails(std::string playlistID, std::string name, std::string description, bool isPublic = true);
};

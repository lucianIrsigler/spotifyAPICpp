#pragma once
#include "base.h"


/*Class used for interaction with information about Artists*/
class spotifyArtists :
    public base
{
public:
	//empty construtor
	spotifyArtists() :base() {};

	spotifyArtists(
		std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect) :
		base(authToken, userspotifyClientID, userClientSecret, userRedirect) {
		spotifyLogToFile("Created:" + std::string(typeid(*this).name()));
	};

	//GET

	/**
		Gets an artist's albums.Scopes:NONE
		@param ID-> artist's ID
		@param include_groups-> The type of albums to include. Valid entries: album|single|appears_on|compilation
		@param market-> Specific market to search for
		@param limit -> Number of albums to include
		@param offset -> Offset from first album to start on
		@returns JSON response body
	*/
	std::string getArtistAlbums(std::string ID, std::string include_groups = "", std::string market = "", int limit = 10, int offset = 0);
	
	/*
		Returns similar artists to the given Artist.Scopes:NONE
		@param ID->Artist's ID
		@returns JSON response body containing artists
	*/
	std::string getArtistRelatedArtists(std::string ID);

	/*
		Gets an artist's top tracks.Scopes:NONE
		@param ID->Artist ID to search for
		@param market-> Specific market to search for
		@returns JSON response body containing the top tracks
	*/
	std::string getArtistTopTracks(std::string ID, std::string market = "");

	/*
		Gets information about an artist.Scopes:NONE
		@param ID->artist to search for
		@returns JSON response body containing information about the artist
	*/
	std::string getArtist(std::string ID);

	/*
		Gets information about several artists.Scopes:NONE
		@param ID->artists to search for
		@returns JSON response body containing information about the artist
	*/
	std::string getArtists(std::string IDs);
};


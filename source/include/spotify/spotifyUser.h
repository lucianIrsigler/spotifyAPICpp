#pragma once
#include "base.h"

/*
	Class for interacting with user info
*/
class spotifyUser :
    public base
{
public:
	//User info
	spotifyUser();
	spotifyUser(
		std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect);
	spotifyUser(spotifyInfo* clientInformation);

	/*
		Performs a cURL request for user data.Scopes:NONE
		@returns readBuffer->User data in JSON form
	*/
	std::string getUserInfo();

	/*
		Performs a cURL request for the user's display name.Scopes:NONE
		@returns userInfo->user's display name
	*/
	std::string getDisplayName();

	/*
		Performs a cURL request for the user's URL.Scopes:NONE
		@returns userInfo->user's URL
	*/
	std::string getUserURL();

	/*
		Performs a cURL request for the user's followers amount.Scopes:NONE
		@returns followers->number of follows the user has
	*/
	int getUserFollowers();

	/*
		Performs a cURL request for the user's ID.Scopes:NONE
		@returns userInfo->user's ID
	*/
	std::string getUserID();

	/*
		Performs a cURL request for the user's profile picture source.Scopes:NONE
		@returns userInfo->user's profile picture source
	*/
	std::string getUserProfilePictureURL();
	
	/*
		Performs a cURL request for the user's type.Scopes:NONE
		@returns userInfo->user's type
	*/
	std::string getUserType();

	/*
		Performs a cURL request for the user's URI.Scopes:NONE
		@returns userInfo->user's URI
	*/
	std::string getUserURI();

	/*
		Gets a user's top tracks/artists.Scopes:NONE
		@param type-> type of item to search for. Valid:artists|tracks
		@param time_range->Period of time to search over. Valid:long_term|medium_term|short_term
		@param limit->Number of entries to return
		@param offset->Offset from the first
		@returns JSON response containing info about top tracks/artists
	*/
	std::string getUserTopItems(std::string type, std::string time_range="medium_term", int limit = 10, int offset = 0);
};


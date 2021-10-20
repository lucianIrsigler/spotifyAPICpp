#pragma once
#include "base.h"
class spotifyUser :
    public base
{
public:
	//User info
	spotifyUser() :base() {};
	spotifyUser(
		std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect) :
		base(authToken, userspotifyClientID, userClientSecret, userRedirect) {
		spotifyLogToFile("Created:" + __class__);
	};


	std::string getUserInfo();
	std::string getDisplayName();
	std::string getUserURL();
	int getUserFollowers();
	std::string getUserID();
	std::string getUserProfilePictureURL();
	std::string getUserType();
	std::string getUserURI();
};


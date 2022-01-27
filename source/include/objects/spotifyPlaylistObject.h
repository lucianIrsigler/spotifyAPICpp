#pragma once
#include <string>


class spotifyPlaylistObject
{
public:
	std::string name;
	std::string href;
	std::string description;
	std::string id;
	std::string playlistURL;
	std::string snapshotID;
	std::string tracksURL;
	bool isPublic;
	int totalNumberOfTracks;
};


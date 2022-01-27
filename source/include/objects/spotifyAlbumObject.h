#pragma once
#include "spotifyTrackObject.h"

class spotifyAlbumObject
{
public:
	std::string name;
	std::string releaseDate;
	int totalTracks;
	std::vector<spotifyTrackObject> tracks;
};


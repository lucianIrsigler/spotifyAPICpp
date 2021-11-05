#pragma once

#include <string>
#include <vector>

class spotifyTrackObject
{
public:
	spotifyTrackObject(std::string artistName,
		std::string givenID,
		bool trackIsExplicit) :
		artist(artistName), ID(givenID), isExplicit(trackIsExplicit) {}
		
	std::string artist;
	std::string ID;
	bool isExplicit;
};


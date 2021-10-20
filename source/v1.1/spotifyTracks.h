#pragma once
#include "base.h"
#include <string>

class spotifyTracks :
    public base
{
public:
	spotifyTracks() :base() {};
	spotifyTracks(
		std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect) :
		base(authToken, userspotifyClientID, userClientSecret, userRedirect) {
		spotifyLogToFile("Created:" + std::string(typeid(*this).name()));
	};

    //GET
	std::string getTrackAudioAnalysis(std::string ID);
	std::string getTracksAudioAnalysis(std::string IDs);
	std::string getTrackAudioFeatures(std::string ID);
	std::string getTrack(std::string market, std::string ID);
	std::string getTracks(std::string market, std::string IDs);
};


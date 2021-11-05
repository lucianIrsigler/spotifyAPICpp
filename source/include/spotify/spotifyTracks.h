#pragma once
#include "base.h"

/*
	Class used for searching information on tracks
*/
class spotifyTracks :
    public base
{
public:
	spotifyTracks();
	spotifyTracks(
		std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect);
	spotifyTracks(spotifyInfo* clientInformation);

    //GET

	/*
		Does an audio analysis of a track
		@param ID->ID of track
		@returns JSON response containing the audio analysis
	*/
	std::string getTrackAudioAnalysis(std::string ID);
	
	/*
		Does an audio analysis of several track
		@param IDs->IDs of the tracks(comma-seperated)
		@returns JSON response containing the audio analysis

	*/
	std::string getTracksAudioAnalysis(std::string IDs);
	
	/*
		Gets audio feature for a track
		@param ID->ID of track
		@returns JSON response containing audio features
	*/
	std::string getTrackAudioFeatures(std::string ID);

	/*
		Gets information on a track
		@param ID->ID of track
		@param market->specific market to search for
		@returns JSON response containing track information
	*/
	std::string getTrack(std::string ID, std::string market);

	/*
		Gets information on several track
		@param IDs->IDs of track(comma-seperated)
		@param market->specific market to search for
		@returns JSON response containing tracks information
	*/
	std::string getTracks(std::string IDs, std::string market);
};


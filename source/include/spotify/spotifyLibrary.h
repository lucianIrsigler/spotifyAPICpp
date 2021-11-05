#pragma once
#include "base.h"

class spotifyLibrary :
    public base
{
public:
	spotifyLibrary();
	spotifyLibrary(
		std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect);

	spotifyLibrary(spotifyInfo* clientInformation);

	//DELETE

	void removeAlbums(std::string IDs);
	void removeEpisodes(std::string IDS);
	void removeShows(std::string IDs, std::string market="");
	void removeTracks(std::string IDs);

	//GET

	std::string checkSavedAlbums(std::string IDs);
	std::string checkSavedEpisodes(std::string IDs);
	std::string checkSavedShows(std::string IDs);
	std::string checkSavedTracks(std::string IDs);
	std::string getSavedAlbums(std::string market = "", int limit = 20, int offset = 0);
	std::string getSavedEpisodes(std::string market = "", int limit = 20, int offset = 0);
	std::string getSavedShows(int limit = 20, int offset = 0);

	//user-library-read
	std::string getSavedTracks(std::string market = "", int limit = 20, int offset = 0);
	
	//SAVED TRACKS

	int numberOfSavedTracks();


	//PUT

	void saveAlbum(std::string IDs);
	void saveEpisodes(std::string IDs);
	void saveShows(std::string IDs);
	void saveTracks(std::string IDs);
};


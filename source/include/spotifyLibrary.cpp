#include "spotifyLibrary.h"

spotifyLibrary::spotifyLibrary() :base()
{
};

spotifyLibrary::spotifyLibrary(
	std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect) :
	base(authToken, userspotifyClientID, userClientSecret, userRedirect)
{
};

spotifyLibrary::spotifyLibrary(spotifyClientInfo* clientInformation) :
	base(clientInformation)
{
};

/*
user-library-modify
*/
void spotifyLibrary::removeAlbums(std::string IDs) {
	//https://developer.spotify.com/console/delete-current-user-saved-albums/

	//user-library-modify

	std::string url = "https://api.spotify.com/v1/me/albums?ids=" + IDs;

	std::string readBuffer = performCURLDELETE(url, "", authenticityToken);

	errorChecking(readBuffer, __func__);
}

/*
*/
void spotifyLibrary::removeEpisodes(std::string IDs) {
	//https://developer.spotify.com/console/delete-current-user-saved-episodes/

	//user-library-modify

	std::string url = "https://api.spotify.com/v1/me/episodes?ids" + IDs;

	std::string readBuffer = performCURLDELETE(url, "", authenticityToken);

	errorChecking(readBuffer, __func__);

}
void spotifyLibrary::removeShows(std::string IDs, std::string market) {
	//https://developer.spotify.com/console/delete-current-user-saved-shows/

	std::string url = "https://api.spotify.com/v1/me/shows?ids=" + IDs;

	if (market != "") {
		url += "market=" + market;
	}

	std::string readBuffer = performCURLDELETE(url, "", authenticityToken);

	errorChecking(readBuffer, __func__);
}

void spotifyLibrary::removeTracks(std::string IDs) {
	//https://developer.spotify.com/console/delete-current-user-saved-tracks/

	std::string url = "https://api.spotify.com/v1/me/tracks?ids=" + IDs;

	std::string readBuffer = performCURLDELETE(url, "", authenticityToken);

	errorChecking(readBuffer, __func__);
}


//user-library-read
std::string spotifyLibrary::isSavedAlbums(std::string IDs) {
	//https://developer.spotify.com/console/get-current-user-contains-saved-episodes/

	std::string url = "https://api.spotify.com/v1/me/albums/contains?ids=" + IDs;

	std::string readBuffer = performCURLGET(url, authenticityToken);

	return errorChecking(readBuffer,  __func__);
}

/*
*/
std::string spotifyLibrary::isSavedEpisodes(std::string IDs) {
	//https://developer.spotify.com/console/get-current-user-contains-saved-shows/

	std::string url = "https://api.spotify.com/v1/me/episodes/contains?ids=" + IDs;

	std::string readBuffer = performCURLGET(url, authenticityToken);

	return errorChecking(readBuffer,  __func__);
}


std::string spotifyLibrary::isSavedShows(std::string IDs) {
	//https://developer.spotify.com/console/get-current-user-contains-saved-shows/

	std::string url = "https://api.spotify.com/v1/me/shows/contains?ids=" + IDs;

	std::string readBuffer = performCURLGET(url, authenticityToken);

	return errorChecking(readBuffer,  __func__);
}


std::string spotifyLibrary::isSavedTracks(std::string IDs) {
	//https://developer.spotify.com/console/get-current-user-contains-saved-tracks/

	std::string url = "https://api.spotify.com/v1/me/tracks/contains?ids=" + IDs;

	std::string readBuffer = performCURLGET(url, authenticityToken);

	return errorChecking(readBuffer,  __func__);

}


std::string spotifyLibrary::getSavedAlbums(std::string market,int limit, int offset) {
	//https://developer.spotify.com/console/get-current-user-saved-albums/

	if (isLimitsAndOffsetInvalid(limit, offset)) {
		spotifyLogToFile(std::string(__func__)+"->Invalid limit / offset.\nLimit:" + std::to_string(limit) + "\nOffset:" + std::to_string(offset));
		return "ERROR: Invalid limit/offset";
	}

	std::string url = "https://api.spotify.com/v1/me/albums?limit=" + std::to_string(limit)
		+ "&offset=" + std::to_string(offset);

	if (market != "") {
		url += "&market=" + market;
	}

	std::string readBuffer = performCURLGET(url, authenticityToken);

	return errorChecking(readBuffer,  __func__);

}


/*
user-library-read user-read-playback-position
*/
std::string spotifyLibrary::getSavedEpisodes(std::string market, int limit, int offset) {
	//https://developer.spotify.com/console/get-current-user-saved-episodes/

	if (isLimitsAndOffsetInvalid(limit, offset)) {
		spotifyLogToFile(std::string(__func__) + "->Invalid limit / offset.\nLimit:" + std::to_string(limit) + "\nOffset:" + std::to_string(offset));
		return "ERROR: Invalid limit/offset";
	}
	std::string url;
	
	
	std::string readBuffer = performCURLGET(url, authenticityToken);

	return errorChecking(readBuffer,  __func__);
}

/*
user-library-read
*/
std::string spotifyLibrary::getSavedShows(int limit, int offset) {
	//https://developer.spotify.com/console/get-current-user-saved-shows/

	if (isLimitsAndOffsetInvalid(limit, offset)) {
		spotifyLogToFile(std::string(__func__) + "->Invalid limit / offset.\nLimit:" + std::to_string(limit) + "\nOffset:" + std::to_string(offset));
		return "ERROR: Invalid limit/offset";
	}

	std::string url = "https://api.spotify.com/v1/me/shows?limit=" 
		+ std::to_string(limit)
		+ "&offset=" + std::to_string(offset);
	
	std::string readBuffer = performCURLGET(url, authenticityToken);

	return errorChecking(readBuffer,  __func__);
}

/**
	Gets the user's saved tracks
	@param market->Market to search for
	@param limit->max number of tracks to get
	@param offset->offset from first
	@return JSON request of n number of track information
*/
std::string spotifyLibrary::getSavedTracks(std::string market, int limit, int offset) {
	//https://developer.spotify.com/console/get-current-user-saved-tracks/

	if (isLimitsAndOffsetInvalid(limit, offset)) {
		spotifyLogToFile(std::string(__func__) + "->Invalid limit / offset.\nLimit:" + std::to_string(limit) + "\nOffset:" + std::to_string(offset));
		return "ERROR: Invalid limit/offset";
	}

	std::string url;

	if (market != "") {
		url += "https://api.spotify.com/v1/me/tracks?market=" + market
			+ "&limit=" + std::to_string(limit)
			+ "&offset=" + std::to_string(offset);
	}
	else {

		url += "https://api.spotify.com/v1/me/tracks?limit=" + std::to_string(limit)
			+ "&offset=" + std::to_string(offset);
	}

	std::string readBuffer = performCURLGET(url, authenticityToken);

	return errorChecking(readBuffer,  __func__);

}


/*
*/
int spotifyLibrary::numberOfSavedTracks() {
	std::string text = getSavedTracks();
	int first = text.find("\"total\"");
	std::string total = text.substr(first+10,text.find_last_of("}")- first-11);
	
	return std::stoi(total);
}

/**/
void spotifyLibrary::saveAlbum(std::string IDs) {
	//https://developer.spotify.com/console/put-current-user-saved-albums/

	std::string url = "https://api.spotify.com/v1/me/albums?ids=" + IDs;

	std::string readBuffer = performCURLPUT(url, "", authenticityToken);

	errorChecking(readBuffer, __func__);

}


void spotifyLibrary::saveEpisodes(std::string IDs) {
	//https://developer.spotify.com/console/put-current-user-saved-episodes/

	std::string url = "https://api.spotify.com/v1/me/episodes?ids=" + IDs;

	std::string readBuffer = performCURLPUT(url, "", authenticityToken);

	errorChecking(readBuffer, __func__);
}


void spotifyLibrary::saveShows(std::string IDs) {
	//https://developer.spotify.com/console/put-current-user-saved-shows/


	std::string url = "https://api.spotify.com/v1/me/shows?ids=" + IDs;

	std::string readBuffer = performCURLPUT(url, "", authenticityToken);

	errorChecking(readBuffer, __func__);
}


void spotifyLibrary::saveTracks(std::string IDs) {
	//https://developer.spotify.com/console/put-current-user-saved-tracks/

	std::string url = "https://api.spotify.com/v1/me/tracks?ids=" + IDs;

	std::string readBuffer = performCURLPUT(url, "", authenticityToken);

	errorChecking(readBuffer, __func__);
}
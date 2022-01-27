#include "spotifyTracks.h"

spotifyTracks::spotifyTracks() :base()
{
	
};

spotifyTracks::spotifyTracks(
	std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect) :
	base(authToken, userspotifyClientID, userClientSecret, userRedirect)
{
	
	
};

spotifyTracks::spotifyTracks(spotifyClientInfo* clientInformation) :
	base(clientInformation)
{
	
	
};
/*
*/
std::string spotifyTracks::getTrackAudioAnalysis(std::string ID) {
	//https://developer.spotify.com/console/get-audio-analysis-track/

	std::string url = "https://api.spotify.com/v1/audio-analysis/" + ID;

	std::string readBuffer = performCURLGET(url, authenticityToken);

	return errorChecking(readBuffer,  __func__);
}

/*
*/
std::string spotifyTracks::getTracksAudioAnalysis(std::string IDs) {
	//https://developer.spotify.com/console/get-audio-features-several-tracks/

	std::string url = "https://api.spotify.com/v1/audio-features?ids=" + IDs;

	std::string readBuffer = performCURLGET(url, authenticityToken);

	return errorChecking(readBuffer,  __func__);
}

/*
*/
std::string spotifyTracks::getTrackAudioFeatures(std::string ID) {
	//https://developer.spotify.com/console/get-audio-features-track/

	std::string url = "https://api.spotify.com/v1/audio-features/" + ID;

	std::string readBuffer = performCURLGET(url, authenticityToken);

	return errorChecking(readBuffer,  __func__);
}



std::string spotifyTracks::getTrack(std::string ID, std::string market) {
	//https://developer.spotify.com/console/get-track/

	std::string url = "https://api.spotify.com/v1/tracks/" + ID;

	if (market != "") {
		url += "?market=" + market;
	}

	std::string readBuffer = performCURLGET(url, authenticityToken);

	return errorChecking(readBuffer,  __func__);
}

spotifyTrackObject spotifyTracks::getTrack(std::string ID, std::string market, std::string ignore) {
	//https://developer.spotify.com/console/get-track/

	std::string url = "https://api.spotify.com/v1/tracks/" + ID;

	if (market != "") {
		url += "?market=" + market;
	}

	std::string readBuffer = performCURLGET(url, authenticityToken);

	std::string temp = errorChecking(readBuffer, __func__);

	spotifyTrackObject tempObj;

	return tempObj;
}



std::string spotifyTracks::getTracks(std::string IDs,std::string market) {
	std::string url="";

	if (market != "") {
		url += "https://api.spotify.com/v1/tracks/?market=" + market+"&ids="+IDs;

	}
	else {
		url += "https://api.spotify.com/v1/tracks/?ids=" + IDs;
	}

	std::string readBuffer = performCURLGET(url, authenticityToken);

	return errorChecking(readBuffer,  __func__);

}

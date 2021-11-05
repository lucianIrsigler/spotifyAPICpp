#include "spotifyTracks.h"

spotifyTracks::spotifyTracks() :base()
{
	_className = __class__;
};

spotifyTracks::spotifyTracks(
	std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect) :
	base(authToken, userspotifyClientID, userClientSecret, userRedirect)
{
	spotifyLogToFile("Created:" + __class__);
	_className = __class__;
};

spotifyTracks::spotifyTracks(spotifyInfo* clientInformation) :
	base(clientInformation)
{
	spotifyLogToFile("Created:" + __class__);
	_className = __class__;
};
/*
*/
std::string spotifyTracks::getTrackAudioAnalysis(std::string ID) {
	//https://developer.spotify.com/console/get-audio-analysis-track/

	std::string url = "https://api.spotify.com/v1/audio-analysis/" + ID;

	std::string readBuffer = performCURLGET(url, spotifyAuthenticityToken);

	return utility::errorChecking(readBuffer, __class__, __func__);
}

/*
*/
std::string spotifyTracks::getTracksAudioAnalysis(std::string IDs) {
	//https://developer.spotify.com/console/get-audio-features-several-tracks/

	std::string url = "https://api.spotify.com/v1/audio-features?ids=" + IDs;

	std::string readBuffer = performCURLGET(url, spotifyAuthenticityToken);

	return utility::errorChecking(readBuffer, __class__, __func__);
}

/*
*/
std::string spotifyTracks::getTrackAudioFeatures(std::string ID) {
	//https://developer.spotify.com/console/get-audio-features-track/

	std::string url = "https://api.spotify.com/v1/audio-features/" + ID;

	std::string readBuffer = performCURLGET(url, spotifyAuthenticityToken);

	return utility::errorChecking(readBuffer, __class__, __func__);
}

/*
*/
std::string spotifyTracks::getTrack(std::string ID, std::string market) {
	//https://developer.spotify.com/console/get-track/

	std::string url = "https://api.spotify.com/v1/tracks/" + ID;

	if (market != "") {
		url += "?market=" + market;
	}

	std::string readBuffer = performCURLGET(url, spotifyAuthenticityToken);

	return utility::errorChecking(readBuffer, __class__, __func__);
}

/*
*/
std::string spotifyTracks::getTracks(std::string IDs,std::string market) {
	std::string url="";

	if (market != "") {
		url += "https://api.spotify.com/v1/tracks/?market=" + market+"&ids="+IDs;

	}
	else {
		url += "https://api.spotify.com/v1/tracks/?ids=" + IDs;
	}

	std::string readBuffer = performCURLGET(url, spotifyAuthenticityToken);

	return utility::errorChecking(readBuffer, __class__, __func__);

}

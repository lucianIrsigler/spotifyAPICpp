#include "pch.h"
#include "followers.h"

/*
	Checks conditions. ie) types and IDS. if there is an error. std::exception is thrown
*/
void  spotifyFollower::checkConditions(std::string& type, std::string IDS, std::string functionName) {
	if (type != "artist" && type != "user") {
		throw spotifyException(functionName + "->Invalid type\ntype:" + type);
	}
	else if ((std::count(IDS.begin(), IDS.end(), ',') > 49) && (IDS != "")) {
		throw spotifyException(functionName + "->Too many requests(>50)");
	}
}

spotifyFollower::spotifyFollower() :SpotifyBase()
{
};

spotifyFollower::spotifyFollower(
	std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect) :
	SpotifyBase(authToken, userspotifyClientID, userClientSecret, userRedirect)
{
};


//DELETE

void spotifyFollower::unfollowArtists(std::string type, std::string IDS) {
	//https://developer.spotify.com/console/delete-following/

	try {
		checkConditions(type, IDS, __func__);
	}
	catch (spotifyException e) {
		return;
	}
	
	std::string JSONobject;
	
	std::string url = "https://api.spotify.com/v1/me/following?type=" + type;

	if (IDS != "") {
		url += "&ids=" + IDS;

		std::string readBuffer = performCURLDELETE(url, "", authenticityToken);
		errorChecking(readBuffer, __func__);
	}
}

/*
playlist-modify-public playlist-modify-private
*/
void spotifyFollower::unfollowPlaylist(std::string playlistID) {
	//https://developer.spotify.com/console/delete-playlist-followers

	std::string url = "https://api.spotify.com/v1/playlists/" + playlistID + "/followers";

	std::string readBuffer = performCURLDELETE(url, "", authenticityToken);

	errorChecking(readBuffer, __func__);
};

//GET

/*
user-follow-read
*/
std::string spotifyFollower::isUserFollowing(std::string type, std::string IDS) {
	//https://developer.spotify.com/documentation/web-api/reference/#/operations/check-current-user-follows

	try {
		checkConditions(type, IDS, __func__);
	}
	catch (spotifyException& e) {
		spotifyLogToFile(e.what());
		return e.what();
	}

	std::string url = "https://api.spotify.com/v1/me/following/contains?type="+type+"&ids="+ IDS;
	std::string readBuffer = performCURLGET(url, authenticityToken);

	return errorChecking(readBuffer,  __func__);
};

/**/
std::string spotifyFollower::getFollowing(std::string type, std::string after, int limit) {
	//https://developer.spotify.com/console/get-following/

	try {
		checkConditions(type, "", __func__);
	}
	catch (spotifyException& e) {
		spotifyLogToFile(e.what());
		return e.what();
	}

	std::string url = "https://api.spotify.com/v1/me/following?type=" + type;

	if (after != "") {
		url += "&after=" + after;
	}

	url += "&limit=" + std::to_string(limit);

	std::string readBuffer = performCURLGET(url, authenticityToken);

	return errorChecking(readBuffer,  __func__);
};

//PUT
/*
playlist-modify-public playlist-modify-private
*/
void spotifyFollower::followPlaylist(std::string playlistID, bool isPublicOnProfile) {
	//https://developer.spotify.com/console/put-playlist-followers/

	std::string url = "https://api.spotify.com/v1/playlists/" + playlistID + "/followers";
	
	std::string jsonQuery = "{\"public\":";
	(isPublicOnProfile) ? jsonQuery += "true}" : jsonQuery += "false}";

	std::string JSONbody = json::convertToJSONObject(jsonQuery);

	std::string readBuffer = performCURLPUT(url, JSONbody, authenticityToken);

	errorChecking(readBuffer, __func__);
};

void spotifyFollower::followArtistOrUser(std::string type, std::string IDS) {
	//https://developer.spotify.com/console/put-following/

	try {
		checkConditions(type, IDS, __func__);
	}
	catch (spotifyException e) {
		spotifyLogToFile(e.what());
		return;
	}

	std::string JSONobject;

	std::string url = "https://api.spotify.com/v1/me/following?type=" + type;
	
	if (IDS != "") {
		url += "&ids=" + IDS;
		std::cout << url << std::endl;
		std::string readBuffer = performCURLPUT(url, "{}", authenticityToken);
		errorChecking(readBuffer, __func__);
	}
}

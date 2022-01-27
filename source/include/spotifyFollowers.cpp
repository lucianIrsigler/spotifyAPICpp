#include "spotifyFollowers.h"

inline void checkAFollowersFunctionCondtions(std::string& type, std::string IDS, std::string functionName) {

	if (type != "artist" && type != "user") {
		spotifyLogToFile(functionName + "->Invalid type\ntype:" + type);
		throw spotifyException("Invalid type");
	}
	else if ((std::count(IDS.begin(), IDS.end(), ',') > 49) && (IDS != "")) {
		spotifyLogToFile(functionName + "->Too many requests(>50)");
		throw spotifyException("Too many requests");
	}

}

spotifyFollowers::spotifyFollowers() :base()
{
	
};

spotifyFollowers::spotifyFollowers(
	std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect) :
	base(authToken, userspotifyClientID, userClientSecret, userRedirect)
{

};

spotifyFollowers::spotifyFollowers(spotifyClientInfo* clientInformation) :
	base(clientInformation)
{
};


//DELETE

void spotifyFollowers::unfollowArtists(std::string type, std::string IDS) {
	//https://developer.spotify.com/console/delete-following/

	try {
		checkAFollowersFunctionCondtions(type, IDS, __func__);
	}
	catch (spotifyException &e) {
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
void spotifyFollowers::unfollowPlaylist(std::string playlistID) {
	//https://developer.spotify.com/console/delete-playlist-followers

	std::string url = "https://api.spotify.com/v1/playlists/" + playlistID + "/followers";

	std::string readBuffer = performCURLDELETE(url, "", authenticityToken);

	errorChecking(readBuffer, __func__);
};

//GET

/*
user-follow-read
*/
std::string spotifyFollowers::isUserFollowing(std::string type, std::string IDS) {
	//https://developer.spotify.com/console/get-following-contains/

	try {
		checkAFollowersFunctionCondtions(type, IDS, __func__);
	}
	catch (spotifyException& e) {
		return e.what();
	}

	std::string url = "https://api.spotify.com/v1/me/following/contains?type="+type+"&ids="+ IDS;
	std::string readBuffer = performCURLGET(url, authenticityToken);

	return errorChecking(readBuffer,  __func__);
};

/**/
std::string spotifyFollowers::getFollowedArtists(std::string type, std::string after, int limit) {
	//https://developer.spotify.com/console/get-following/

	try {
		checkAFollowersFunctionCondtions(type, "", __func__);
	}
	catch (spotifyException& e) {
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
*/
std::string spotifyFollowers::isFollowingArtistOrUser(std::string type, std::string IDS) {
	//https://developer.spotify.com/documentation/web-api/reference/#/operations/check-current-user-follows

	try {
		checkAFollowersFunctionCondtions(type, "", __func__);
	}
	catch (spotifyException& e) {
		return e.what();
	}

	std::string url = "https://api.spotify.com/v1/me/following/contains?type=" + type;

	if (IDS != "") {
		url += "&ids=" + IDS;
	}

	std::string readBuffer = performCURLGET(url, authenticityToken);

	return errorChecking(readBuffer, __func__);
};

/*
playlist-modify-public playlist-modify-private
*/
void spotifyFollowers::followPlaylist(std::string playlistID, bool isPublicOnProfile) {
	//https://developer.spotify.com/console/put-playlist-followers/

	std::string url = "https://api.spotify.com/v1/playlists/" + playlistID + "/followers";
	
	std::string jsonQuery = "{\"public\":";
	(isPublicOnProfile) ? jsonQuery += "true}" : jsonQuery += "false}";

	std::string JSONbody = json::convertToJSONObject(jsonQuery);

	std::string readBuffer = performCURLPUT(url, JSONbody, authenticityToken);

	errorChecking(readBuffer, __func__);
};

void spotifyFollowers::followArtistOrUser(std::string type, std::string IDS) {
	//https://developer.spotify.com/console/put-following/

	try {
		checkAFollowersFunctionCondtions(type, IDS, __func__);
	}
	catch (spotifyException& e) {
		return;
	}

	std::string JSONobject;

	std::string url = "https://api.spotify.com/v1/me/following?type=" + type;

	if (IDS != "") {
		url += "&ids=" + IDS;
		std::string readBuffer = performCURLPUT(url, "", authenticityToken);
		errorChecking(readBuffer, __func__);
	}
}


//artistsIDs = std::vector<std::string>
	//else if (artistIDS.size() != 0) {

	//	//{ids:["74ASZWbe4lXaubB36ztrGX", "08td7MxkoHQkXnWAYD8d6Q"]}
	//	artistIDS.insert(artistIDS.begin(), "ids");

	//	std::string JSONQuery = "{\"0\":[";
	//	int counter = 1;

	//	while (counter < artistIDS.size() - 1) {
	//		JSONQuery += "\"" + std::to_string(counter) + "\", ";
	//		counter += 1;
	//	}

	//	JSONQuery += "\"" + std::to_string(counter) + "\"]}";

	//	std::string temp = json::convertToJSONString(std::move(JSONQuery), artistIDS);
	//	std::string JSONobject = json::convertToJSONObject(temp);

	//	std::string readBuffer = performCURLPUT(url, JSONobject, authenticityToken);

	//	errorChecking(readBuffer, __func__);
	//}
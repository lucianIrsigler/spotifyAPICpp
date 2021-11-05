#include "spotifyFollowers.h"


spotifyFollowers::spotifyFollowers() :base()
{
	_className = __class__;
};

spotifyFollowers::spotifyFollowers(
	std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect) :
	base(authToken, userspotifyClientID, userClientSecret, userRedirect)
{
	spotifyLogToFile("Created:" + __class__);
	_className = __class__;
};

spotifyFollowers::spotifyFollowers(spotifyInfo* clientInformation) :
	base(clientInformation)
{
	spotifyLogToFile("Created:" + __class__);
	_className = __class__;
};


//DELETE

void spotifyFollowers::unfollowArtists(std::string type, std::string IDS, std::vector<std::string>artistIDS) {
	//https://developer.spotify.com/console/delete-following/

	std::string JSONobject;

	if (type != "artist" && type != "user") {
		spotifyLogToFile("spotifyFollowers::unfollowArist()->Invalid type\ntype:" + type);
		return;
	}
	else if (std::count(IDS.begin(), IDS.end(), ',') > 49) {
		spotifyLogToFile("spotifyFollowers::unfollowArist()->Too many requests(>50)");
		return;
	}

	std::string url = "https://api.spotify.com/v1/me/following?type=" + type;

	if (IDS != "") {
		url += "&ids=" + IDS;

		std::string readBuffer = performCURLDELETE(url, "", spotifyAuthenticityToken);
		utility::errorChecking(readBuffer, __class__, __func__, true);

	}
	else if (artistIDS.size() != 0) {

		//{ids:["74ASZWbe4lXaubB36ztrGX", "08td7MxkoHQkXnWAYD8d6Q"]}
		artistIDS.insert(artistIDS.begin(), "ids");
		std::string JSONQuery = "{\"0\":[";
		int counter = 1;

		while (counter < artistIDS.size() - 1) {
			JSONQuery += "\"" + std::to_string(counter) + "\", ";
			counter += 1;
		}

		JSONQuery += "\"" + std::to_string(counter) + "\"]}";

		std::string temp = json::convertToJSONString(std::move(JSONQuery), artistIDS);
		std::string JSONobject = json::convertToJSONObject(temp);

		std::string readBuffer = performCURLDELETE(url, JSONobject, spotifyAuthenticityToken);

		utility::errorChecking(readBuffer, __class__, __func__, true);
	}
}

/*
playlist-modify-public playlist-modify-private
*/
void spotifyFollowers::unfollowPlaylist(std::string playlistID) {
	//https://developer.spotify.com/console/delete-playlist-followers

	std::string url = "https://api.spotify.com/v1/playlists/" + playlistID + "/followers";

	std::string readBuffer = performCURLDELETE(url, "", spotifyAuthenticityToken);

	utility::errorChecking(readBuffer, __class__, __func__, true);

};

//GET

/*
user-follow-read
*/
std::string spotifyFollowers::checkIfUserFollowsX(std::string type, std::string IDS) {
	//https://developer.spotify.com/console/get-following-contains/

	if (type != "artist" && type != "user") {
		spotifyLogToFile("spotifyFollowers::checkIfUserFollowsX()->Invalid type\ntype:"+type);
		return "";
	}
	else if (std::count(IDS.begin(), IDS.end(), ',') > 49) {
		spotifyLogToFile("spotifyFollowers::unfollowArist()->Too many requests(>50)");
		return "";
	}

	std::string url = "https://api.spotify.com/v1/me/following/contains?type="+type+"&ids="+ IDS;
	std::string readBuffer = performCURLGET(url, spotifyAuthenticityToken);

	return utility::errorChecking(readBuffer, __class__, __func__);
};

/**/
std::string spotifyFollowers::getFollowedArtists(std::string type, std::string after, int limit) {
	//https://developer.spotify.com/console/get-following/

	if (type != "artist" && type != "user") {
		spotifyLogToFile("spotifyFollowers::checkIfUserFollowsX()->Invalid type\ntype:" + type);
		return "";
	}

	std::string url = "https://api.spotify.com/v1/me/following?type=" + type;

	if (after != "") {
		url += "&after=" + after;
	}

	url += "&limit=" + std::to_string(limit);

	std::string readBuffer = performCURLGET(url, spotifyAuthenticityToken);

	return utility::errorChecking(readBuffer, __class__, __func__);

};

//PUT

/*
*/
void spotifyFollowers::followX(std::string type, std::string IDS, std::vector<std::string>& artistIDS) {
	//https://developer.spotify.com/console/put-following/

	std::string JSONobject;

	if (type != "artist" && type != "user") {
		spotifyLogToFile("spotifyFollowers::unfollowArist()->Invalid type\ntype:" + type);
		return;
	}
	else if (std::count(IDS.begin(), IDS.end(), ',') > 49) {
		spotifyLogToFile("spotifyFollowers::unfollowArist()->Too many requests(>50)");
		return;
	}

	std::string url = "https://api.spotify.com/v1/me/following?type=" + type;

	if (IDS != "") {
		url += "&ids=" + IDS;

		std::string readBuffer = performCURLPUT(url, "", spotifyAuthenticityToken);

		utility::errorChecking(readBuffer, __class__, __func__, true);
	}
	else if (artistIDS.size() != 0) {

		//{ids:["74ASZWbe4lXaubB36ztrGX", "08td7MxkoHQkXnWAYD8d6Q"]}
		artistIDS.insert(artistIDS.begin(), "ids");

		std::string JSONQuery = "{\"0\":[";
		int counter = 1;

		while (counter < artistIDS.size() - 1) {
			JSONQuery += "\"" + std::to_string(counter) + "\", ";
			counter += 1;
		}

		JSONQuery += "\"" + std::to_string(counter) + "\"]}";

		std::string temp = json::convertToJSONString(std::move(JSONQuery), artistIDS);
		std::string JSONobject = json::convertToJSONObject(temp);

		std::string readBuffer = performCURLPUT(url, JSONobject, spotifyAuthenticityToken);

		utility::errorChecking(readBuffer, __class__, __func__, true);
	}
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

	std::string readBuffer = performCURLPUT(url, JSONbody, spotifyAuthenticityToken);

	utility::errorChecking(readBuffer, __class__, __func__, true);
};
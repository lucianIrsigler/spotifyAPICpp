#include "pch.h"
#include "playlist.h"

spotifyPlaylist::spotifyPlaylist() :SpotifyBase()
{
    
};

spotifyPlaylist::spotifyPlaylist(
    std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect) :
    SpotifyBase(authToken, userspotifyClientID, userClientSecret, userRedirect)
{
};


std::string spotifyPlaylist::getSearchedUserPlaylists(std::string userID, int limit, int offset) {
    //https://developer.spotify.com/console/get-playlists/
    //playlist-read-private playlist-read-collaborative

    if ( isLimitsAndOffsetInvalid(limit, offset)) {
        spotifyLogToFile("spotifyPlaylist::getSearchedUserPlaylists()->Invalid limit/offset.\nLimit:" + std::to_string(limit) + "\nOffset:" + std::to_string(offset));
        //throw spotifyException("ERROR: Invalid limit/offset");
        return "ERROR: Invalid limit/offset";
    }
    std::string url = "https://api.spotify.com/v1/users/" + userID + "/playlists?" + std::to_string(limit) + "&offset" + std::to_string(offset);

    std::string readBuffer = performCURLGET(url, authenticityToken);

    return errorChecking(readBuffer,  __func__);
}


std::string spotifyPlaylist::getUserPlaylists(int limit, int offset) {
    //https://developer.spotify.com/console/get-current-user-playlists/

    if ( isLimitsAndOffsetInvalid(limit, offset)) {
        spotifyLogToFile("spotifyPlaylist::getUserPlaylists()->Invalid limit/offset.\nLimit:" + std::to_string(limit) + "\nOffset" + std::to_string(offset));
        return "ERROR:Invalid limit/offset";
    }

    //Buffer to write to
    std::string readBuffer = performCURLGET("https://api.spotify.com/v1/me/playlists?" + std::to_string(limit), authenticityToken);

    return errorChecking(readBuffer,  __func__);
}


std::string spotifyPlaylist::getPlaylist(std::string playlistID, std::string market, std::string fields) {
    //https://developer.spotify.com/console/get-playlist/

    std::string url = "https://api.spotify.com/v1/playlists/"
        + playlistID
        + "?market=" + market
        + "fields" + fields;


    std::string readBuffer = performCURLGET(url, authenticityToken);
   
    return errorChecking(readBuffer,  __func__);
}


std::string spotifyPlaylist::getPlaylistCover(std::string playlistID) {
    //https://developer.spotify.com/console/get-playlist-images/

    std::string url = "https://api.spotify.com/v1/playlists/" + playlistID + "/images";


    std::string readBuffer = performCURLGET(url, authenticityToken);

    return errorChecking(readBuffer,  __func__);
}


std::string spotifyPlaylist::getPlaylistItems(std::string playlistID, std::string market, std::string fields, int limit, int offset) {
    //https://developer.spotify.com/console/get-playlist-tracks/

    if ( isLimitsAndOffsetInvalid(limit, offset)) {
        spotifyLogToFile("spotifyPlaylist::getPlaylistItems()->Invalid limit/offset.\nLimit:" + std::to_string(limit) + "\nOffset" + std::to_string(offset));
        return "ERROR:Invalid limit/offset";
    }

    std::string url = "https://api.spotify.com/v1/playlists/" + playlistID + "/tracks?";

    if (market != "") {
        url += "market=" + market;
    }
    if (fields != "") {
        url = "&fields=" + fields;
    }

    url += "&limit=" + std::to_string(limit);
    url += "&offset=" + std::to_string(offset);

    std::string readBuffer = performCURLGET(url, authenticityToken);

    return errorChecking(readBuffer,  __func__);
}


void spotifyPlaylist::createPlaylist(std::string userID, std::string name, std::string description, bool isPublic) {
    //https://developer.spotify.com/console/post-playlists/

    //playlist-modify-public playlist-modify-private
    if (name.length() == 0) {
        spotifyLogToFile("spotifyPlaylist::createPlaylist()->name too short");
    }

    std::string publicString;
    isPublic ? publicString = "true" : publicString = "false";

    std::vector<std::string>areas = { "name",name,"description",description,"public",publicString };

    ///{0:1,2:3,4,5}
    //{"name":"","description":"","public":true}
    std::string temp = json::convertToJSONString("{\"0\":\"1\",\"2\":\"3\",\"4\":5}", areas);

    std::string JSONobject = json::convertToJSONObject(temp);

    std::string readBuffer = performCURLPOST("https://api.spotify.com/v1/users/" + userID + "/playlists", JSONobject, authenticityToken);

    errorChecking(readBuffer, __func__);
}

void spotifyPlaylist::addItemToPlaylist(std::string playlistID, std::string URI, int position, std::vector<std::string> URIS) {
    //https://developer.spotify.com/console/post-playlist-tracks/

    //playlist-modify-public playlist-modify-private  

    // {\"0\" : [\"1\",\"2\",\"3\"...\"n\"]}

    URIS.insert(URIS.begin(), "uris");

    std::string JSONQuery = "{\"0\" : [";
    size_t counter = 1;

    while (counter < URIS.size() - 1) {
        JSONQuery += "\"" + std::to_string(counter) + "\",";
        counter += 1;
    }

    JSONQuery += "\"" + std::to_string(counter++) + "\"]}";


    std::string temp = json::convertToJSONString(std::move(JSONQuery), URIS);

    std::string JSONobject = json::convertToJSONObject(temp);

    std::string postData = "position" + std::to_string(position);

    if (URI != "") {
        postData += "&uris=" + URI;
    }

    std::string url = "https://api.spotify.com/v1/playlists/" + playlistID + "/tracks?" + postData;

    std::string readBuffer = performCURLPOST(url, JSONobject, authenticityToken);

    errorChecking(readBuffer, __func__);
}


void spotifyPlaylist::deleteItemFromPlaylist(std::string playlistID, std::vector<std::string> URIS) {
    //https://developer.spotify.com/console/delete-playlist-tracks/

    //playlist-modify-public playlist-modify-private

    std::string JSONString = "{ \"tracks\": [";

    for (size_t i = 0; i < URIS.size() - 1; i++) {
        JSONString += "{ \"uri\": \"" + URIS[i] + "\" },";
    }

    JSONString += "{ \"uri\": \"" + URIS[URIS.size() - 1] + "\" }" + "] }";


    std::string JSONobject = json::convertToJSONObject(JSONString);

    std::string url = "https://api.spotify.com/v1/playlists/" + playlistID + "/tracks";
    std::string readBuffer = performCURLPOST(url, JSONobject, authenticityToken);

    errorChecking(readBuffer, __func__);
    //{ "tracks": [{ "uri": "spotify:track:4iV5W9uYEdYUVa79Axb7Rh" },{ "uri": "spotify:track:1301WleyT98MSxVHPZCA6M" }] }
}
//{1:[{2:3},{2:3}]}

//{"uris": ["spotify:track:4iV5W9uYEdYUVa79Axb7Rh","spotify:track:1301WleyT98MSxVHPZCA6M", "spotify:episode:512ojhOuo1ktJprKbVcKyQ"]}
//{1:[2,3,4]}


void spotifyPlaylist::updatePlaylistItems(std::string playlistID, std::string URIs, std::string requestBody) {
    //https://developer.spotify.com/console/put-playlist-tracks/

    //playlist-modify-public playlist-modify-private

}


void spotifyPlaylist::changePlaylistDetails(std::string playlistID, std::string name, std::string description, bool isPublic) {
    //https://developer.spotify.com/console/put-playlist/
    if (name.length() == 0) {
        spotifyLogToFile("spotifyPlaylist::changePlaylistDetails()->name too short");
    }

    std::string publicString;
    isPublic ? publicString = "true" : publicString = "false";

    std::vector<std::string>areas = { "name",name,"description",description,"public", publicString };

    std::string temp = json::convertToJSONString("{\"0\":\"1\",\n  \"2\":\"3\",\n  \"4\":5\n}", areas);
    //std::string temp = R"({"name":"vibey","description":"description","public":true})";

    std::string JSONobject = json::convertToJSONObject(temp);

    std::string url = "https://api.spotify.com/v1/playlists/" + playlistID;

    std::string readBuffer = performCURLPUT(url, JSONobject, authenticityToken);

    std::cout << JSONobject << std::endl;
    std::cout << temp << std::endl;
    std::cout << readBuffer << std::endl;
    errorChecking(readBuffer, __func__);
}

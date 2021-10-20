#pragma once
#include "base.h"
#include <string>
#include <vector>
#include "json.h"
class spotifyFollowers :
    public base
{
public:
    spotifyFollowers() :base() {};
    spotifyFollowers(
        std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect) :
        base(authToken, userspotifyClientID, userClientSecret, userRedirect) {
    };

    //DELETE
    void unfollowArtist(std::string type, std::string IDS, std::vector<std::string>artistIDS);
    void unfollowPlaylist(std::string playlistID);

    //GET
    std::string checkIfUserFollowsX(std::string type, std::string ids);
    std::string getFollowedArtists(std::string type, std::string after, int limit=20);

    //PUT
    void followX(std::string type, std::string IDS, std::vector<std::string>& artistIDS);
    void followPlaylist(std::string playlistID, bool isPublicOnProfile);

};


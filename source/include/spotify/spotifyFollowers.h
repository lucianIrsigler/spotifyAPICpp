#pragma once
#include "base.h"
#include "json.h"

/*
    Class used to change a User's following/unfollowing
*/
class spotifyFollowers :
    public base
{
public:
    spotifyFollowers();
    spotifyFollowers(
        std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect);

    spotifyFollowers(spotifyInfo* clientInformation);

    //DELETE

    /*
        Unfollows artists on the User's behalf.Scopes:user-follow-modify
        @param type-> ID type. Valid:artist|user
        @param IDs->Comma seperated list of Artist IDs
        @param artistIDS-> same as IDs, but in vector format
    */
    void unfollowArtists(std::string type, std::string IDS, std::vector<std::string>artistIDS);

    /*
        Unfollows a playlist on the User's behalf.Scopes:playlist-modify-public playlist-modify-private
        @param playlistID-> ID of playlist to unfollow
    */
    void unfollowPlaylist(std::string playlistID);

    //GET

    /**/
    std::string checkIfUserFollowsX(std::string type, std::string ids);
    std::string getFollowedArtists(std::string type, std::string after, int limit=20);

    //PUT

    /*
        Follows artists/users on the User's behalf.Scopes:user-follow-modify
        @param type-> ID type. Valid:artist|user
        @param IDs->Comma seperated list of Artist IDs
        @param artistIDS-> same as IDs, but in vector format
    */
    void followX(std::string type, std::string IDS, std::vector<std::string>& artistIDS);

    /*
       Follows a playlist on the User's behalf.Scopes:playlist-modify-public playlist-modify-private
       @param playlistID-> ID of playlist to unfollow
       @param isPublicOnProfile->Whether the playlist should appear public on the user profile.
    */
    void followPlaylist(std::string playlistID, bool isPublicOnProfile);
};


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

    spotifyFollowers(spotifyClientInfo* clientInformation);

    //DELETE

    /*
        Unfollows artists on the User's behalf.Scopes:user-follow-modify
        @param type-> ID type. Valid:artist|user
        @param IDs->Comma seperated list of Artist IDs
    */
    void unfollowArtists(std::string type, std::string IDS);

    /*
        Unfollows a playlist on the User's behalf.Scopes:playlist-modify-public playlist-modify-private
        @param playlistID-> ID of playlist to unfollow
    */
    void unfollowPlaylist(std::string playlistID);

    //GET

    /**/
    std::string isUserFollowing(std::string type, std::string ids);
    std::string getFollowedArtists(std::string type, std::string after, int limit=20);

    //PUT

    /*
        Follows artists/users on the User's behalf.Scopes:user-follow-modify
        @param type-> ID type. Valid:artist|user
        @param IDs->Comma seperated list of Artist IDs
    */
    std::string isFollowingArtistOrUser(std::string type, std::string IDS);

    /*
       Follows a playlist on the User's behalf.Scopes:playlist-modify-public playlist-modify-private
       @param playlistID-> ID of playlist to unfollow
       @param isPublicOnProfile->Whether the playlist should appear public on the user profile.
    */
    void followPlaylist(std::string playlistID, bool isPublicOnProfile);

    /*
       Follows an artist.Scopes:user-follow-modify
       @param type- type of spotify consumer to follow. ie) artist/user
       @param IDS - comma seperated string containing user ID's to follow. Max 50
    */
    void followArtistOrUser(std::string type, std::string IDS);
};


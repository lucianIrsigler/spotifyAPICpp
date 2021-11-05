#include "spotifyPlayer.h"


spotifyPlayer::spotifyPlayer() :base()
{
    _className = __class__;
};

spotifyPlayer::spotifyPlayer(
    std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect) :
    base(authToken, userspotifyClientID, userClientSecret, userRedirect)
{
    spotifyLogToFile("Created:" + __class__);
    _className = __class__;
};

spotifyPlayer::spotifyPlayer(spotifyInfo * clientInformation) :
    base(clientInformation)
{
    spotifyLogToFile("Created:" + __class__);
    _className = __class__;
};


//Player

std::string spotifyPlayer::getUserRecentPlaying(int limit) {
    //https://developer.spotify.com/console/get-recently-played/

    //user-read-recently-played

    //acquires user data and stores in variable readBuffer
    std::string readBuffer = performCURLGET("https://api.spotify.com/v1/me/player/recently-played", spotifyAuthenticityToken);
    return utility::errorChecking(readBuffer, __class__, __func__);
}

/*

*/
std::string spotifyPlayer::getUserPlaybackState(std::string additional_types, std::string market) {
    //https://developer.spotify.com/console/get-user-player/
    
    //user-read-playback-state

    //acquires user data and stores in variable readBuffer
    std::string readBuffer = performCURLGET("	https://api.spotify.com/v1/me/player", spotifyAuthenticityToken);

    return utility::errorChecking(readBuffer, __class__, __func__);
}

/*

*/
std::string spotifyPlayer::getAvialableDevices() {
    //https://developer.spotify.com/console/get-users-available-devices/
    //user-read-playback-state

    std::string readBuffer = performCURLGET("https://api.spotify.com/v1/me/player/devices", spotifyAuthenticityToken);


    return utility::errorChecking(readBuffer, __class__, __func__);
}

/*

*/
std::string spotifyPlayer::getUserCurrentPlaying() {
    //user-read-currently-playing
    // 
    //acquires user data and stores in variable readBuffer
    std::string readBuffer = performCURLGET("https://api.spotify.com/v1/me/player/currently-playing", spotifyAuthenticityToken);
    
    return utility::errorChecking(readBuffer, __class__, __func__);
}


/*

*/
void spotifyPlayer::skipToNextTrack(std::string deviceID) {
    //https://developer.spotify.com/console/post-next/

    //user-modify-playback-state

    std::string readBuffer = performCURLPOST("https://api.spotify.com/v1/me/player/next", "", spotifyAuthenticityToken);

    utility::errorChecking(readBuffer, __class__, __func__, true);
}

/*

*/
void spotifyPlayer::skipToPreviousTrack(std::string deviceID) {
    //https://developer.spotify.com/console/post-previous/

    //user-modify-playback-state

    std::string readBuffer = performCURLPOST("https://api.spotify.com/v1/me/player/previous", "", spotifyAuthenticityToken);

    utility::errorChecking(readBuffer, __class__, __func__, true);
}

/*

*/
void spotifyPlayer::addSongToUserQueue(std::string URI, std::string deviceID) {
//https://developer.spotify.com/console/post-queue/
    //user-modify-playback-state

    std::string url = "https://api.spotify.com/v1/me/player/queue?uri=" + URI;

    if (deviceID != "") {
        url += "&device_id=" + deviceID;
    }

    std::string readBuffer = performCURLPOST(url, "", spotifyAuthenticityToken);

    utility::errorChecking(readBuffer, __class__, __func__, true);
}

/*

*/
void spotifyPlayer::transferUserPlayback(std::string deviceIDs,bool startPlaying) {
    //https://developer.spotify.com/console/put-user-player/
    //user-modify-playback-state

    /*{
        "device_ids": [
            "74ASZWbe4lXaubB36ztrGX"
        ]
    }*/

    std::string jsonRequest = "{\"device_ids\": [\""+ deviceIDs +"\"])";

    std::string jsonObject = json::convertToJSONObject(jsonRequest);

    std::string readBuffer = performCURLPUT("https://api.spotify.com/v1/me/player", jsonObject, spotifyAuthenticityToken);

    utility::errorChecking(readBuffer, __class__, __func__, true);
}


/*

*/
void spotifyPlayer::resumeUserPlayback() noexcept {
    //https://developer.spotify.com/console/put-play/


}

/*
user-modify-playback-state
*/
void spotifyPlayer::pauseUserPlayback(std::string deviceID) noexcept {
    //https://developer.spotify.com/console/put-pause/


    std::string readBuffer = performCURLPUT("https://api.spotify.com/v1/me/player/pause", "", spotifyAuthenticityToken);
}



/*

*/
void spotifyPlayer::seekToPositionCurrentTrack() {

}

/*

*/
void spotifyPlayer::setRepeatOnPlayback(std::string state, std::string deviceID) {
    //https://developer.spotify.com/console/put-repeat/

    /*track will repeat the current track.
    context will repeat the current context.
    off will turn repeat off.*/

    if (state == "track" || state == "context" || state == "off") {
        std::string url = "https://api.spotify.com/v1/me/player/repeat?state=" + state;

        if (deviceID != "") {
            url += "&device_id" + deviceID;
        }

        std::string readBuffer = performCURLPUT(url, "", spotifyAuthenticityToken);
        std::cout << readBuffer << std::endl;
        utility::errorChecking(readBuffer, __class__, __func__, true);
    }
    else {
        throw spotifyException("Invalid state");
    }
}

/*

*/
void spotifyPlayer::setVolumeOnPlayback(int volume, std::string deviceID) {
    //https://developer.spotify.com/console/put-volume/

    if ((0 > volume) || (volume > 100)) {
        throw spotifyException("Invalid volume.");
    }

    //user-modify-playback-state


    std::string url = "https://api.spotify.com/v1/me/player/volume?volume_percent=" + std::to_string(volume);

    if (deviceID != "") {
        url += "&device_id=" + deviceID;
    }

    std::string readBuffer = performCURLPUT(url, "", spotifyAuthenticityToken);

    utility::errorChecking(readBuffer, __class__, __func__, true);

}

/*

*/
void spotifyPlayer::toggleShuffleOnPlayback(bool shuffle, std::string deviceID) {
    // https://developer.spotify.com/console/put-shuffle/

    /*
    true- shuffle
    false- does not shuffle
    */

    //user-modify-playback-state


    std::string state;

    shuffle ? state = "true" : state = "false";

    std::string url = "https://api.spotify.com/v1/me/player/shuffle?state=" + state + "&&device_id=" + deviceID;

    std::string readBuffer = performCURLPUT(url, "", spotifyAuthenticityToken);

    utility::errorChecking(readBuffer, __class__, __func__, true);
}
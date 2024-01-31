#include "pch.h"
#include "player.h"


spotifyPlayer::spotifyPlayer() :SpotifyBase()
{
};

spotifyPlayer::spotifyPlayer(
    std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect) :
    SpotifyBase(authToken, userspotifyClientID, userClientSecret, userRedirect)
{
};

//Player

std::string spotifyPlayer::getUserRecentPlaying(int limit) {
    //https://developer.spotify.com/console/get-recently-played/

    //user-read-recently-played

    //acquires user data and stores in variable readBuffer
    std::string readBuffer = performCURLGET("https://api.spotify.com/v1/me/player/recently-played", authenticityToken);

    return errorChecking(readBuffer, __func__);
}

/*

*/
std::string spotifyPlayer::getUserPlaybackState(std::string additional_types, std::string market) {
    //https://developer.spotify.com/console/get-user-player/
    //acquires user data and stores in variable readBuffer
    std::string readBuffer = performCURLGET("https://api.spotify.com/v1/me/player", authenticityToken);

    return errorChecking(readBuffer, __func__);
}

/*

*/
std::string spotifyPlayer::getAvailableDevices() {
    //https://developer.spotify.com/console/get-users-available-devices/
    //user-read-playback-state

    std::string readBuffer = performCURLGET("https://api.spotify.com/v1/me/player/devices", authenticityToken);

    return errorChecking(readBuffer, __func__);
}

/*

*/
std::vector<std::string> spotifyPlayer ::getQueueSongs() {
    //https://developer.spotify.com/documentation/web-api/reference/get-queue
    //user-read-playback-state
    std::string readBuffer = performCURLGET("https://api.spotify.com/v1/me/player/queue", authenticityToken);

    //spotify:track:[a-zA-z0-9]+
    std::regex pattern ("spotify:track:[a-zA-z0-9]+");

    auto results = regexUtility::executeRegex(pattern, readBuffer);

    return results;
}
/*

*/
const std::string spotifyPlayer::getUserCurrentPlaying() {
    //user-read-currently-playing
    // 
    //acquires user data and stores in variable readBuffer
    std::string readBuffer = performCURLGET("https://api.spotify.com/v1/me/player/currently-playing", authenticityToken);

    return errorChecking(readBuffer, __func__);
}


/*

*/
void spotifyPlayer::skipToNextTrack(std::string deviceID) {
    //https://developer.spotify.com/console/post-next/

    //user-modify-playback-state

    std::string readBuffer = performCURLPOST("https://api.spotify.com/v1/me/player/next", "", authenticityToken);

    errorChecking(readBuffer, __func__);
}


void spotifyPlayer::skipToPreviousTrack(std::string deviceID) {
    //https://developer.spotify.com/console/post-previous/

    //user-modify-playback-state

    std::string readBuffer = performCURLPOST("https://api.spotify.com/v1/me/player/previous", "", authenticityToken);

    errorChecking(readBuffer, __func__);
}


void spotifyPlayer::addSongToUserQueue(std::string URI, std::string deviceID) {
    //https://developer.spotify.com/console/post-queue/
    //user-modify-playback-state


    std::string url = "https://api.spotify.com/v1/me/player/queue?uri=" + URI;

    if (deviceID != "") {
        url += "&device_id=" + deviceID;
    }

    std::string readBuffer = performCURLPOST(url, "", authenticityToken);

    errorChecking(readBuffer, __func__);
}

/*

*/
void spotifyPlayer::transferUserPlayback(std::string deviceIDs, bool startPlaying) {
    //https://developer.spotify.com/console/put-user-player/
    //user-modify-playback-state

    /*{
        "device_ids": [
            "74ASZWbe4lXaubB36ztrGX"
        ]
    }*/

    std::string jsonRequest = "{\"device_ids\": [\"" + deviceIDs + "\"])";

    std::string jsonObject = json::convertToJSONObject(jsonRequest);

    std::string readBuffer = performCURLPUT("https://api.spotify.com/v1/me/player", jsonObject, authenticityToken);

    errorChecking(readBuffer, __func__);
}


//user-modify-playback-state user-read-currently-playing
void spotifyPlayer::resumeUserPlayback(std::string deviceID) {
    //https://developer.spotify.com/console/put-play/

    // Gets current user's playing information
    std::string currentPlaying = getUserCurrentPlaying();

    //Gets spotify album uri
    //std::string uri = extractValueFromString(currentPlaying, "uri", currentPlaying.find("available_markets"));

    std::string uri = regexUtility::executeRegexString(regexUtility::albumRegex, currentPlaying);

    //Get track number
    std::string trackNumberString = extractNumberFromString(currentPlaying, "track_number");
    
    //"\"progress_ms\":\\s(\\d+)"
    const std::regex progressTimeRegex("\"progress_ms\"\\s*:\\s*(\\d+)");
    //Get progress ms
    //std::string progress_ms = extractNumberFromString(currentPlaying, "progress_ms");
    std::cout << currentPlaying << "\n";

    std::string progress_msRegexMatch = regexUtility::executeRegexString(progressTimeRegex, currentPlaying);

    std::string progress_ms = progress_msRegexMatch.substr(16,progress_msRegexMatch.length() - 16);

    //Track numbers use 0 indexing
    std::string trackNumber = std::to_string(std::stoi(trackNumberString) - 1);

    //converts the string to JSON
    std::vector<std::string>areas = {uri,trackNumber,progress_ms };

    std::string temp = json::convertToJSONString(
        "{\"context_uri\":\"0\",\"offset\": {\"position\": 1},\"position_ms\": 2}", areas);

    std::cout << temp<<"\n";
    //std::string JSONobject = json::convertToJSONObject(temp);

    std::string readBuffer;

    readBuffer = performCURLPUT("https://api.spotify.com/v1/me/player/play", temp, authenticityToken);

    errorChecking(readBuffer, __func__);
}


void spotifyPlayer::playTrack(const std::string albumURI, int trackNumber) {
    //https://developer.spotify.com/documentation/web-api/reference/start-a-users-playback
    std::vector<std::string>areas{ albumURI,std::to_string(trackNumber) };

    std::string temp = "{\"context_uri\":\"" + areas[0] + "\",\"offset\": {\"position\": " + areas[1] + "},\"position_ms\": 0}\"";

    std::string readBuffer;

    readBuffer = performCURLPUT("https://api.spotify.com/v1/me/player/play", temp, authenticityToken);

    errorChecking(readBuffer, __func__);
}

/*
user-modify-playback-state
*/
void spotifyPlayer::pauseUserPlayback(std::string deviceID) noexcept {
    //https://developer.spotify.com/console/put-pause/
    std::string readBuffer = performCURLPUT("https://api.spotify.com/v1/me/player/pause", "", authenticityToken);
}


/*

*/
void spotifyPlayer::seekToPositionCurrentTrack() {

}


void spotifyPlayer::setRepeatOnPlayback(const std::string state, std::string deviceID) {
    //https://developer.spotify.com/console/put-repeat/

    /*track will repeat the current track.
    context will repeat the current context.
    off will turn repeat off.*/

    if (state == "track" || state == "context" || state == "off") {
        std::string url = "https://api.spotify.com/v1/me/player/repeat?state=" + state;

        if (deviceID != "") {
            url += "&device_id" + deviceID;
        }

        std::string readBuffer = performCURLPUT(url, "", authenticityToken);

        errorChecking(readBuffer, __func__);
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

    std::string readBuffer = performCURLPUT(url, "", authenticityToken);

    errorChecking(readBuffer, __func__);

}

/*

*/
void spotifyPlayer::toggleShuffleOnPlayback(std::string deviceID) {
    // https://developer.spotify.com/console/put-shuffle/

    /*
    true- shuffle
    false- does not shuffle
    */

    //user-modify-playback-state
    
    //toggle shuffleState
    toggleShuffle = !toggleShuffle;
    
    std::string state;
    std::string device;

    toggleShuffle ? state = "true" : state = "false";
    deviceID == "" ? device = "" : device = "&device_id=" + deviceID;

    std::string url = "https://api.spotify.com/v1/me/player/shuffle?state=" + state+device;

    std::string readBuffer = performCURLPUT(url, "", authenticityToken);

    errorChecking(readBuffer, __func__);
}
#pragma once
#include "base.h"
class spotifyPlayer :
    public base
{
public:
	spotifyPlayer() :base() {};
	spotifyPlayer(
		std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect) :
		base(authToken, userspotifyClientID, userClientSecret, userRedirect){
		spotifyLogToFile("Created:" + __class__);
	};

	//GET
	std::string getUserRecentPlaying(int limit);
	std::string getUserPlaybackState();
	std::string getAvialableDevices();
	std::string getUserCurrentPlaying();

	//POST
	void addSongToUserQueue(std::string URI, std::string deviceID);
	void skipToNextTrack(std::string deviceID);
	void skipToPreviousTrack(std::string deviceID);

	//PUT
	
	void transferUserPlayback();
	void resumeUserPlayback() noexcept;
	void pauseUserPlayback(std::string deviceID) noexcept;
	void seekToPositionCurrentTrack();
	void setRepeatOnPlayback(std::string state, std::string deviceID);
	void setVolumeOnPlayback(int volume, std::string deviceID);
	void toggleShuffleOnPlayback(bool shuffle, std::string deviceID);
};


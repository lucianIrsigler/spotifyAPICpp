#pragma once
#include "spotifyBase.h"
#include <vector>
#include <string>
#include <regex>

/*
	Player class controls the playing of tracks
*/
class spotifyPlayer :
	public SpotifyBase
{
public:
	//vars
	bool toggleShuffle = false;

	spotifyPlayer();

	spotifyPlayer(
		std::string authToken, std::string userspotifyClientID, std::string userClientSecret, std::string userRedirect);

	//GET

	/*
		Gets the User's recently played tracks.Scopes:user-read-recently-played
		@param limit->Number of songs to retrieve
		@returns JSON response containing information about recently played tracks
	*/
	std::string getUserRecentPlaying(int limit);


	/*
		Gets information about the user's current played type and device .Scopes:user-read-playback-state
		@param limit->Number of songs to retrieve
		@returns JSON response containing information about recently played tracks
	*/
	std::string getUserPlaybackState(std::string additional_types = "", std::string market = "");

	/*
		Gets information on the User's available devices.Scopes:user-read-playback-state
		@returns JSON response containing information about the devices available
	*/
	std::string getAvailableDevices();

	/*
		gets the songs in the user's queue.
		@returns vector containing the songs urls
	*/
	std::vector<std::string>getQueueSongs();


	/*
		Gets the user's currently playing track.Scopes:user-read-currently-playing
		@returns JSON response containing track information
		*/
	const std::string getUserCurrentPlaying();

	//POST

	/*
		Adds song to the user's queue.Scopes:user-modify-playback-state
		@param URI->song URI to add
		@param deviceID->Which device to add the song to. If left as ""->then current device is selected
	*/
	void addSongToUserQueue(std::string URI, std::string deviceID = "");

	/*
		Skips to the next song.Scopes:user-modify-playback-state
		@param deviceID->ID of device to target. If left as "", then current device is selected
	*/
	void skipToNextTrack(std::string deviceID = "");

	/*

	*/
	void skipToPreviousTrack(std::string deviceID = "");

	//PUT
	/*
		Transfer playback to new device and if it should start playing.Scopes:user-modify-playback-state
		@param deviceIDs->ID of the device to switch to
		@param startPlaying->Ensures the current playback happens on the new device
	*/
	void transferUserPlayback(std::string deviceIDs, bool startPlaying);

	/*
	*/
	void resumeUserPlayback(std::string deviceID = "");

	/*
		Plays a track.
		@param uri - spotify:track:<> to play
		@param deviceID - device to play on. Defaults to current device
	*/

	void playTrack(const std::string albumURI, int trackNumber);

	/*
		Pauses the user's current playback.Scopes:user-modify-playback-state
		@param deviceID->Playback to pause. if left as "", pauses current playback
	*/
	void pauseUserPlayback(std::string deviceID = "") noexcept;

	/**/
	void seekToPositionCurrentTrack();

	/*
		Sets the current playback to repeat.Scope:user-modify-playback-state
		@param state->State of repeat to set. Valid:track|context|off. Track->current track; context->current contexnt;
		off->turn repeat off
		@param deviceID->Playback to set teh repeat on
	*/
	void setRepeatOnPlayback(const std::string state, std::string deviceID = "");

	/*
		Sets the playback to a certain volume.Scope:user-modify-playback-state
		@param volume->Volume to set playback to
		@param deviceID->ID of playback whose volume should be set
	*/
	void setVolumeOnPlayback(int volume, std::string deviceID = "");

	/*
		Toggles shuffle.Scope:user-modify-playback-state
		@param shuffle->If the player should shuffle
		@param deviceID->Which device the shuffle should be toggled for
	*/
	void toggleShuffleOnPlayback(std::string deviceID = "");



};


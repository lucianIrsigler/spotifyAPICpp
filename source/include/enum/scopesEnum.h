#pragma once

//If you want to use all the functions in a class, this enum provides all the scopes required for the class
enum scopes {
	player,
	tracks,
	users
};

std::string toString(scopes v) {
	switch (v) {
	case player:
		return "user-modify-playback-state user-read-currently-playing user-read-playback-state";
	case tracks:
		return "";
	case users:
		return "user-follow-modify";
	default:
		return "invalid scope enum";
	}
}
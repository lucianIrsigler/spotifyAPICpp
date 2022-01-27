/*
	test.h
	Purpose:Provide testing namespace for classes/methods

	@author Lucian Irsigler
	@version 1.1
*/

#pragma once
#include "spotifylogging.h"
#include "spotifyPlaylist.h"
#include "spotifyTracks.h"
#include "spotifyArtists.h"
#include <fstream>

namespace testing {
	namespace logging {
		void testFully() {
			spotifyLogToFile("");
			spotifyLogToFile("THIS IS A MESSAGE");
			spotifyLogToFile(std::to_string(-1));
			spotifyLogToFile("THIs\n\n\nis\n\n\ta\n\nmessage ok");
		}
	}

	namespace playlist {

		void testFully() {
			std::ofstream filePlaylist("playlistTEST.txt", std::fstream::app);

			spotifyPlaylist test = spotifyPlaylist("",
				"8939a122f64f4d89bdb9d457f3457a2b",
				"25708c369d9f4e43be6680dc3fdd1e90",
				"https://www.google.com");


			std::string scopes = "playlist-read-private playlist-read-collaborative";

			test.basicauthorize(scopes);

			std::cout << "TEST getSearchedUserPlaylists" << "\n";
			filePlaylist << "TEST getSearchedUserPlaylists" << "\n";
			filePlaylist << test.getSearchedUserPlaylists("ki09vo7tt3rwgyrsma9lhjo4c") << "\n";
			filePlaylist << test.getSearchedUserPlaylists("ki09vo7tt3rwgc") << "\n";
			filePlaylist << test.getSearchedUserPlaylists("ki09vo7tt3rwgyrsma9lhjo4c", 10, 0) << "\n";
			filePlaylist << test.getSearchedUserPlaylists("ki09vo7tt3rwgyrsma9lhjo4c", 100, 0) << "\n";
			filePlaylist << test.getSearchedUserPlaylists("ki09vo7tt3rwgyrsma9lhjo4c", -1, 2) << "\n";
			filePlaylist << test.getSearchedUserPlaylists("ki09vo7tt3rwg9lhjo4c", 10, 0) << "\n";

			std::cout << "TEST getUserPlaylists" << "\n";
			filePlaylist << "TEST getUserPlaylists" << "\n";
			filePlaylist << test.getUserPlaylists() << "\n";
			filePlaylist << test.getUserPlaylists(20, 1) << "\n";
			filePlaylist << test.getUserPlaylists(51, 0) << "\n";
			filePlaylist << test.getUserPlaylists(-1, 0) << "\n";
			filePlaylist << test.getUserPlaylists(20, -10) << "\n";

			std::cout << "TEST getPlaylist" << "\n";
			filePlaylist << "TEST getPlaylist" << "\n";
			filePlaylist << test.getPlaylist("", "", "") << "\n";
			filePlaylist << test.getPlaylist("0hP5KYEs9K99jMNgBS3IOi", "", "") << "\n";
			filePlaylist << test.getPlaylist("0hP5KYEs9K99jMNg", "", "") << "\n";
			filePlaylist << test.getPlaylist("0hP5KYEs9K99jMNgBS3IOi", "DSDS", "") << "\n";
			filePlaylist << test.getPlaylist("dasdsad", "ES", "") << "\n";

			std::cout << "TEST getPlaylistCover" << "\n";
			filePlaylist << "TEST getPlaylistCover" << "\n";
			filePlaylist << test.getPlaylistCover("") << "\n";
			filePlaylist << test.getPlaylistCover("0hP5KYEs9K99jMNgBS3IOi") << "\n";
			filePlaylist << test.getPlaylistCover("0hP5KYEs9K99jM") << "\n";

			std::cout << "TEST getPlaylistItems" << "\n";
			filePlaylist << "TEST getPlaylistItems" << "\n";
			filePlaylist << test.getPlaylistItems("", "", "") << "\n";
			filePlaylist << test.getPlaylistItems("0hP5KYEs9K99jMNgBS3IOi", "", "") << "\n";
			filePlaylist << test.getPlaylistItems("0hP5KYEs9K99jM", "", "") << "\n";
			filePlaylist << test.getPlaylistItems("0hP5KYEs9K99jMNgBS3IOi", "dsds", "") << "\n";
			filePlaylist << test.getPlaylistItems("0hP5KYEs9K99jMNgBS3IOi", "", "dasdas") << "\n";
			filePlaylist << test.getPlaylistItems("0hP5KYEs9K99jMNgBS3IOi", "", "", 20, 0) << "\n";
			filePlaylist << test.getPlaylistItems("0hP5KYEs9K99jMNgBS3IOi", "", "", 51, 1) << "\n";
			filePlaylist << test.getPlaylistItems("0hP5KYEs9K99jMNgBS3IOi", "", "", -1, 0) << "\n";

			filePlaylist.close();
		}
	}

	namespace track {
		void testFully() {
			std::ofstream fileTrack("trackTEST.txt", std::fstream::app);

			std::string tracks = "36fwOQjsEFesQvfEybK2Ei,59nbIJxGb1qkrzbtTomZkL,5OCJzvD7sykQEKHH7qAC3C,0YammaEkYSeo9vQYZ1OwS6,6c1QaQHdDhtFMfUkhueuXK,4e5WTCvy6Z8hkUY1IP29b0,4qULqxfCRhJAXVc75UupQB,4EpNQjLsdhjO1EGQ1aycTU,7HOYkw4m0lSDxcramohtPl,6LoQHIo74tOzQ8EsLEkhgF";

			spotifyTracks test = spotifyTracks("",
				"8939a122f64f4d89bdb9d457f3457a2b",
				"25708c369d9f4e43be6680dc3fdd1e90",
				"https://www.google.com");

			test.basicauthorize();

			std::cout << "TEST getTrackAudioAnalysis" << "\n";
			fileTrack << "TEST getTrackAudioAnalysis" << "\n";
			fileTrack << test.getTrackAudioAnalysis("015jLlgBeSkl3CApWJhlv7") << "\n";
			fileTrack << test.getTrackAudioAnalysis("dsdsdsd") << "\n";
			fileTrack << test.getTrackAudioAnalysis("") << "\n";

			std::cout << "TEST getTrack" << "\n";
			fileTrack << "TEST getTrack" << "\n";
			fileTrack << test.getTrack("", "015jLlgBeSkl3CApWJhlv7");
			fileTrack << test.getTrack("ESnDF", "015jLlgBeSkl3CApWJhlv7");
			fileTrack << test.getTrack("", "015jLlgBeSkl3CApW");
			fileTrack << test.getTrack("DSSD", "015jLlgBeSkl3CApW");

			std::cout << "TEST getTrackAudioFeatures" << "\n";
			fileTrack << "TEST getTrackAudioFeatures" << "\n";
			fileTrack << test.getTrackAudioFeatures("015jLlgBeSkl3CApWJhlv7") << "\n";
			fileTrack << test.getTrackAudioFeatures("dsdsdsd") << "\n";
			fileTrack << test.getTrackAudioFeatures("") << "\n";

			std::cout << "TEST getTracks" << "\n";
			fileTrack << "TEST getTracks" << "\n";
			fileTrack << test.getTracks("", tracks) << "\n";
			fileTrack << test.getTracks("", "") << "\n";
			fileTrack << test.getTracks("", "DSDASDAS,dsdasdas,gfggf,trtr,dasdas,5454sdsds") << "\n";

			std::cout << "TEST getTracksAudioAnalysis" << "\n";
			fileTrack << "TEST getTracksAudioAnalysis" << "\n";
			fileTrack << test.getTracksAudioAnalysis(tracks) << "\n";
			fileTrack << test.getTracksAudioAnalysis("DSDASASDAS,gfgfgf,66565,dsdas,Sdetujfdf") << "\n";
			fileTrack << test.getTracksAudioAnalysis("") << "\n";

			fileTrack.close();

		}
	}
	namespace artists {
		void testFully() {
			std::ofstream fileArtist("artistsTEST.txt", std::fstream::app);

			spotifyArtists test = spotifyArtists("",
				"8939a122f64f4d89bdb9d457f3457a2b",
				"25708c369d9f4e43be6680dc3fdd1e90",
				"https://www.google.com");

			std::string ID = "0X2BH1fck6amBIoJhDVmmJ";
			std::string IDs = "3lPSkTq1kiSuxDcr996Nlm," + ID;

			test.basicauthorize();


			std::cout << "TEST getArtist" << "\n";
			fileArtist << "TEST getArtist" << "\n";
			
			fileArtist << test.getArtist("") << "\n";
			fileArtist << test.getArtist(ID) << "\n";

			std::cout << "TEST getArtistAlbums" << "\n";
			fileArtist << "TEST getArtistAlbums" << "\n";
			fileArtist << test.getArtistAlbums("") << "\n";
			fileArtist << test.getArtistAlbums(ID) << "\n";
			fileArtist << test.getArtistAlbums(ID, "ok") << "\n";
			fileArtist << test.getArtistAlbums(ID, "single") << "\n";

			std::cout << "TEST getArtistRelatedArtists" << "\n";
			fileArtist << "TEST getArtistRelatedArtists" << "\n";
			fileArtist << test.getArtistRelatedArtists("") << "\n";
			fileArtist << test.getArtistRelatedArtists(ID) << "\n";

			std::cout << "TEST getArtistTopTracks" << "\n";
			fileArtist << "TEST getArtistTopTracks" << "\n";
			fileArtist << test.getArtistTopTracks("") << "\n";
			fileArtist << test.getArtistTopTracks(ID) << "\n";

			std::cout << "TEST getArtists" << "\n";
			fileArtist << "TEST getArtists" << "\n";
			fileArtist << test.getArtists(IDs) << "\n";
			fileArtist << test.getArtists(ID) << "\n";
			fileArtist << test.getArtists("") << "\n";

			fileArtist.close();
		}
	}
}
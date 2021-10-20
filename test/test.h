#pragma once

#include "spotifylogging.h"
#include "spotifyPlaylist.h"
#include "spotifyTracks.h"

namespace testing {
	namespace logging {
		void testA() {
			spotifyLogToFile("");
			spotifyLogToFile("THIS IS A MESSAGE");
			spotifyLogToFile(std::to_string(-1));
			spotifyLogToFile("THIs\n\n\nis\n\n\ta\n\nmessage ok");
		}
	}

	namespace playlist {
		spotifyPlaylist test= spotifyPlaylist("",
			"",
			"",
			"https://www.google.com");

		

		void testA() {
			std::cout << "\n\nTESTA\n\n";
			std::string scopes = "playlist-read-private playlist-read-collaborative";

			test.basicauthorize(scopes);

			std::cout<<test.getSearchedUserPlaylists("ki09vo7tt3rwgyrsma9lhjo4c")<<std::endl;
			std::cout << test.getSearchedUserPlaylists("ki09vo7tt3rwgc") << std::endl;
			std::cout << test.getSearchedUserPlaylists("ki09vo7tt3rwgyrsma9lhjo4c",10,0) << std::endl;
			std::cout << test.getSearchedUserPlaylists("ki09vo7tt3rwgyrsma9lhjo4c",100,0) << std::endl;
			std::cout << test.getSearchedUserPlaylists("ki09vo7tt3rwgyrsma9lhjo4c",-1,2) << std::endl;
			std::cout << test.getSearchedUserPlaylists("ki09vo7tt3rwg9lhjo4c",10,0) << std::endl;
		}

		void testB() {
			std::cout << "\n\nTESTB\n\n";
			std::string scopes = "playlist-read-private";
			test.basicauthorize(scopes);

			std::cout << test.getUserPlaylists() << std::endl;
			std::cout << "\n";
			std::cout << test.getUserPlaylists(20,1) << std::endl;
			std::cout << "\n";
			std::cout << test.getUserPlaylists(51,0) << std::endl;
			std::cout << "\n";
			std::cout << test.getUserPlaylists(-1,0) << std::endl;
			std::cout << "\n";
			std::cout << test.getUserPlaylists(20,-10) << std::endl;
		}

		void testC() {
			std::cout << "\n\nTESTC\n\n";
			std::string scopes = "playlist-read-private";
			test.basicauthorize(scopes);

			std::cout<<test.getPlaylist("0hP5KYEs9K99jMNgBS3IOi","","")<<std::endl;
			std::cout<<test.getPlaylist("0hP5KYEs9K99jMNg","","")<<std::endl;
			std::cout<< test.getPlaylist("0hP5KYEs9K99jMNgBS3IOi","DSDS","") << std::endl;
			std::cout<< test.getPlaylist("dasdsad","ES","") << std::endl;
		}

		void testD() {
			std::cout << "\n\nTESTD\n\n";
			std::string scopes = "playlist-read-private";
			test.basicauthorize(scopes);

			std::cout << test.getPlaylistCover("0hP5KYEs9K99jMNgBS3IOi") << std::endl;
			std::cout << test.getPlaylistCover("0hP5KYEs9K99jM") << std::endl;
		}

		void testE(){
			std::cout << test.getPlaylistItems("0hP5KYEs9K99jMNgBS3IOi","","") << std::endl;
			std::cout << test.getPlaylistItems("0hP5KYEs9K99jM","","") << std::endl;
			std::cout << test.getPlaylistItems("0hP5KYEs9K99jMNgBS3IOi","dsds","") << std::endl;
			std::cout << test.getPlaylistItems("0hP5KYEs9K99jMNgBS3IOi","","dasdas") << std::endl;
			std::cout << test.getPlaylistItems("0hP5KYEs9K99jMNgBS3IOi","","",20,0) << std::endl;
			std::cout << test.getPlaylistItems("0hP5KYEs9K99jMNgBS3IOi","","",51,1) << std::endl;
			std::cout << test.getPlaylistItems("0hP5KYEs9K99jMNgBS3IOi","","",-1,0) << std::endl;
		}

		void fullTest() {
			testA();
			testB();
			testC();
			testD();
			testE();
		}
	}

	namespace track{
		std::string tracks = "36fwOQjsEFesQvfEybK2Ei,59nbIJxGb1qkrzbtTomZkL,5OCJzvD7sykQEKHH7qAC3C,0YammaEkYSeo9vQYZ1OwS6,6c1QaQHdDhtFMfUkhueuXK,4e5WTCvy6Z8hkUY1IP29b0,4qULqxfCRhJAXVc75UupQB,4EpNQjLsdhjO1EGQ1aycTU,7HOYkw4m0lSDxcramohtPl,6LoQHIo74tOzQ8EsLEkhgF";

		spotifyTracks test = spotifyTracks("",
			"",
			"",
			"https://www.google.com");
		
		void testA() {
			test.basicauthorize();
			//std::cout <<test.getTrackAudioAnalysis("015jLlgBeSkl3CApWJhlv7") << std::endl;
			std::cout << test.getTrackAudioAnalysis("dsdsdsd") << std::endl;
			//std::cout << test.getTrackAudioAnalysis("") << std::endl;
		}

		void testB() {
			test.basicauthorize();
			std::cout<<test.getTrack("","015jLlgBeSkl3CApWJhlv7");
			std::cout << test.getTrack("ESnDF","015jLlgBeSkl3CApWJhlv7");
			std::cout << test.getTrack("","015jLlgBeSkl3CApW");
			std::cout << test.getTrack("DSSD","015jLlgBeSkl3CApW");
		}

		void testC() {
			test.basicauthorize();
			std::cout << test.getTrackAudioFeatures("015jLlgBeSkl3CApWJhlv7") << std::endl;
			std::cout << test.getTrackAudioFeatures("dsdsdsd") << std::endl;
			std::cout << test.getTrackAudioFeatures("") << std::endl;
		}

		void testD() {
			test.basicauthorize();
			std::cout << test.getTracks("", tracks) << std::endl;
			std::cout << test.getTracks("", "") << std::endl;
			std::cout << test.getTracks("", "DSDASDAS,dsdasdas,gfggf,trtr,dasdas,5454sdsds") << std::endl;
		}

		void testE() {
			test.basicauthorize();
			std::cout << test.getTracksAudioAnalysis(tracks) << std::endl;
			std::cout << test.getTracksAudioAnalysis("DSDASASDAS,gfgfgf,66565,dsdas,Sdetujfdf") << std::endl;
			std::cout << test.getTracksAudioAnalysis("") << std::endl;
		}
	}
}
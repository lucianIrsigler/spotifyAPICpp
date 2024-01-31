#pragma once
#include <iostream>
#include "player.h"
#include "refreshTokens.h"
#include "enum/scopesEnum.h"

void playerExample() {
    spotifyPlayer player(
        "",
        "57b39f19c5274f328dca3b5e3d144aed",
        "4d7e5f3a23a94347818bcbaab6eb3035",
        "https://www.google.com");


    if (player.checkIfAuthTokenExpired()) {
        player.authorize(toString(scopes::player));
    }

    player.getTokenValuesFromFile();

    while (true) {
        int n;
        std::cin >> n;

        switch (n) {
        case 0:
            exit(0);
        case 1:
            std::cout << player.getUserCurrentPlaying() << "\n";
            break;
        case 2:
            player.skipToNextTrack();
            break;
        case 3:
            player.skipToPreviousTrack();
            break;
        case 4:
            player.pauseUserPlayback();
            break;
        case 5:
            //malformed JSON
            player.resumeUserPlayback();
            break;
        case 6:
            player.toggleShuffleOnPlayback();
            break;
        case 7:
            player.addSongToUserQueue("spotify:track:0x9Vpw90j9fDb669IydnHL");
            break;
        case 8:
            int vol;
            std::cout << "enter volume:";
            std::cin >> vol;

            if (vol < 0 || vol>100) {
                std::cout << "invalid volume\n";
            }
            else {
                player.setVolumeOnPlayback(vol);
            }
            break;
        case 9:
            for (auto x : player.getQueueSongs()) {
                std::cout << x << "\n";
            }
            break;
        default:
            break;
        }
    }
}
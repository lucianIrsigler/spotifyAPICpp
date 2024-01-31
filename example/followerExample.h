#pragma once
#include <iostream>
#include "followers.h"
#include "refreshTokens.h"
#include <enum/scopesEnum.h>


void followerExample(spotifyFollower follower) {
    follower.followArtistOrUser("artist", "6mEQK9m2krja6X1cfsAjfl");
}
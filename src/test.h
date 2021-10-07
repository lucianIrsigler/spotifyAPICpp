/**
    test.h
    Purpose: Provides test functions for spotify class functions

    @author Lucian Irsigler
    @version 1.0 07/10/2021
*/

#pragma once
#include <iostream>
#include "Spotify.h"


void testUser(Spotify& instance) {
    std::cout << instance.getUserInfo() << std::endl;
    std::cout << "Username:" << instance.getDisplayName() << std::endl;
    std::cout << "User URL:" << instance.getUserURL() << std::endl;
    std::cout << "User Followers:" << instance.getUserFollowers() << std::endl;
    std::cout << "User ID:" << instance.getUserID() << std::endl;
    std::cout << "User Profile picture URL:" << instance.getUserProfilePictureURL() << std::endl;
    std::cout << "User Type:" << instance.getUserType() << std::endl;
    std::cout << "User URI:" << instance.getUserURI() << std::endl;
}


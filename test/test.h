/**
    test.h
    Purpose: Provides test functions for spotify class functions

    @author Lucian Irsigler
    @version 1.1 14/10/2021
*/

#pragma once
#include <iostream>
#include "Spotify.h"
#include <assert.h>


void basicAuthorize(Spotify& instance, std::string scopes) {
    try {
        instance.basicauthorize(scopes);
    }
    catch (const spotifyException& error) {
        std::cout << error.what() << std::endl;
        return;
    }
}

void testUser(Spotify& instance) {
    instance.basicauthorize("");

    std::cout << instance.getUserInfo() << std::endl;
    std::cout << "Username:" << instance.getDisplayName() << std::endl;
    std::cout << "User URL:" << instance.getUserURL() << std::endl;
    std::cout << "User Followers:" << instance.getUserFollowers() << std::endl;
    std::cout << "User ID:" << instance.getUserID() << std::endl;
    std::cout << "User Profile picture URL:" << instance.getUserProfilePictureURL() << std::endl;
    std::cout << "User Type:" << instance.getUserType() << std::endl;
    std::cout << "User URI:" << instance.getUserURI() << std::endl;
}

void testPlayer(Spotify& instance) {
    std::cout << instance.getUserCurrentPlaying() << std::endl;
}

void testPlaylist(Spotify& instance) {

    //Test to create playlist
    try {
        instance.createPlaylist(instance.getUserID(), "TEST2", "", true);
    }
    catch (const spotifyException& error) {
        std::cout << error.what() << std::endl;
    }

    //Test to get playlist items
    try {
        std::cout << instance.getPlaylistItems("7hmCqxCjbXqBWnjQ6HNjch", "", "", 10, 0);
    }
    catch (const spotifyException& error) {
        std::cout << error.what() << std::endl;
    }

    //Test to add items to playlist/delete from playlist
    std::vector<std::string>tracks = { "spotify:track:1BIENruTnjKdB7HD2YIlRr","spotify:track:2VOomzT6VavJOGBeySqaMc" };
    try {
        instance.addItemToPlaylist("1jWc7Y22userB4guI2rD38", "", 0, tracks);
    }
    catch (const spotifyException& error) {
        std::cout << error.what() << std::endl;
        return;
    }

    try {
        instance.deleteItemFromPlaylist("1jWc7Y22userB4guI2rD38", tracks);
    }
    catch (const spotifyException& error) {
        std::cout << error.what() << std::endl;
        return;
    }
}


void testJson() {
    //{1:[2,3,4]}
    //{1:[{2:3},{2:3}]}
    std::vector<std::string>values = { "test1","test2","test3","test4","test5","test6","test7" };


    std::string result0 = utility::convertToJSONString("{0:[1,2,3]}", values);
    assert(result0 == "{test1:[test2,test3,test4]}");

    std::string result1 = utility::convertToJSONString("{0:[1:2],3}", values);

    assert(result1 == "{test1:[test2:test3],test4}");

    std::string result2 = utility::convertToJSONString("{0:[[1:2],3]}", values);
    assert(result2 == "{test1:[[test2:test3],test4]}");

    std::string result3 = utility::convertToJSONString("{0:{1:2,1:3,1:4}}", values);
    assert(result3 == "{test1:{test2:test3,test2:test4,test2:test5}}");

    std::cout << "END" << std::endl;

}

void testTextGeneration() {
    for (int i = 0; i < 100; i++) {
        std::cout << utility::generateRandomText(15) << std::endl;
    }
}

void breakPlaylist(Spotify& instance) {
    instance.createPlaylist(instance.getUserID(), "d", "", true);

}
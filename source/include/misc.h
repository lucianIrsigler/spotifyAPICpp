/**
    generation.h
    Purpose: Creates a namespace that contains utility functions for text generation

    @author Lucian Irsigler
    @version 1.1 19/01/2022
*/

#pragma once
#include <string>

namespace {
    /*
        Checks if the limit and offset are invalid.
        @param limit - limit must be within the range of [1,50).
        @param offset - Offset must be within the range of [0,10000).
        @returns true if both limit and offset are invalid, else false
    */
    bool isLimitsAndOffsetInvalid(int limit, int offset) {
        bool isWithinLimit = (1 <= limit && limit < 50);
        bool isWithinAllowedOffset = (0 <= offset && offset < 10000);

        return !(isWithinLimit && isWithinAllowedOffset);
    }

    /*
        Generates a random text of n length
        @param length->length of text to generate
        @returns random text
    */
    std::string generateRandomText(int length) {
        char c;
        std::string message;

        for (int i = 0; i < length; i++) {
            int selection = rand() % 2;
            int random = rand() % 26;

            (selection == 0) ? c = 'a' + random : c = 'A' + random;

            message += c;
        }

        return message;
    }


    /*
        For example:
            https://open.spotify.com/album/7Ixqxq13tWhrbnIabk3172?si=HyKwuofFR26gYWgDcHBemA
            https://open.spotify.com/track/1rDgAHDX95RmylxjgVW9tN?si=849439ed564142b6
            https://open.spotify.com/artist/6mEQK9m2krja6X1cfsAjfl?si=786f53cf49184e34

        This function will retrieive the 7Ixqxq13tWhrbnIabk3172,1rDgAHDX95RmylxjgVW9tN,6mEQK9m2krja6X1cfsAjfl
    */
    std::string getIDFromURL(std::string url) {
        int firstIndex = url.find_last_of('/');
        int secondIndex = url.find("?si");
        return url.substr(firstIndex+1, secondIndex - firstIndex-1);
    }
}
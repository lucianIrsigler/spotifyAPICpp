/**
    generation.h
    Purpose: Creates a namespace that contains utility functions for text generation

    @author Lucian Irsigler
    @version 1.1 19/01/2022
*/

#pragma once
#include <string>

/*
Checks if the limit and offset are invalid.
Limit must be within the range of [1,50).
Offset must be within the range of [0,10000).
Inverse of conjunction is returned- as if both statements are true- then the function returns false

@returns the inverse of the truth Conjunction of the two statements.
*/
static bool isLimitsAndOffsetInvalid(int limit, int offset) {
    bool isWithinLimit = (1 <= limit && limit < 50);
    bool isWithinAllowedOffset = (0 <= offset && offset < 10000);

    return !(isWithinLimit && isWithinAllowedOffset);
}

/*
    Generates a random text of n length
    @param length->length of text to generate
    @returns random text
*/
static std::string generateRandomText(int length) {
    char c;
    std::string message;

    for (uint8_t i = 0; i < length; i++) {
        uint8_t selection = rand() % 2;
        uint8_t random = rand() % 26;

        if (selection == 0) {
            c = 'a' + random;
        }
        else {
            c = 'A' + random;
        }

        message += c;
    }

    return message;
}
#include <iostream>
#include "Spotify.h"

/*
std::string getDefinition() {
    std::string htmlResults = makeRequest("https://www.investopedia.com/financial-term-dictionary-4769738");
    int8_t firstLength = 47; //OFFSET to get start of the definiton
    int32_t firstPos = htmlResults.find("class=\"comp tod__description mntl-text-block\"") + firstLength; //finds start point
    int32_t secondPos = htmlResults.find("</span>", firstPos); // finds end point
    std::string result = htmlResults.substr(firstPos, secondPos - firstPos); //Holds the definition
    return result;
}
*/

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


int main()
{
    std::string token = "";
    Spotify test = Spotify(token, 
        "", 
        "",
        "");

    //test.basicauthorize("");
    //std::cout << test.getUserPlaylists(5) << std::endl;

    std::string scopes = "ugc-image-upload user-library-modify user-read-recently-played";

    std::cin.get();
    return 0;
}
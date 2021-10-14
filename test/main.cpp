#include "test.h"
#include "Spotify.h"



int main()
{
    std::string token = "BQDTbCXfR2q75QgC58Ke2wSOat0JQ8YskPw_aUUWjqUUsBr2wghV_eVayOkzk6VqSC3oka18fiQHkF7gjfrkUaRTp5_X472Zd9FTaVMjlPAsDMhfcrmGXuhgVw9Wu7vYhOh5Po3OOleXSguJvfo7XBZ4nZmgxB9WEFhZ6JeNh7lcl78";
    
    Spotify instance1 = Spotify(token,
        "8939a122f64f4d89bdb9d457f3457a2b",
        "25708c369d9f4e43be6680dc3fdd1e90",
        "https://www.google.com");

    std::string scopes = "user-modify-playback-state user-read-playback-state";

    //instance1.basicauthorize(scopes);

    std::cout << instance1.getAvialableDevices() << std::endl;
    instance1.skipToNextTrack("");

    return 0;
}
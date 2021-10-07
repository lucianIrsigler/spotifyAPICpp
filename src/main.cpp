#include "test.h"

int main()
{
    std::string token = "";
    
    Spotify test = Spotify(token,
        "",
        "",
        "");

    std::string scopes = "";
    test.basicauthorize(scopes);
    std::cin.get();
    return 0;
}

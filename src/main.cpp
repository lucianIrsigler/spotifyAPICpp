#include "test.h"

int main()
{
    std::string token = "BQC-2FVNzili-iPgdOUKGGO0ig3E1XOPNZ8iiaiozmrSg0H1m6tYy0hJaMIVH0qq9Xc1_kZKl2kcGRJDsMUvsLDrtG8qUiRP3ovf0nNZA2qFaml0V3IrU0L30BybtHRcvDlXrSDQnymG0mjrxZSEvqUa6ZK5BbZmGz3HHRTDHZI";
    
    Spotify test = Spotify(token,
        "8939a122f64f4d89bdb9d457f3457a2b",
        "25708c369d9f4e43be6680dc3fdd1e90",
        "https://www.google.com");

    std::string scopes = "ugc-image-upload user-library-modify user-read-recently-played gay-boy";
    test.basicauthorize(scopes);
    std::cin.get();
    return 0;
}
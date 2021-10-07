#include "Spotify.h"

//AUTH source -> https://developer.spotify.com/documentation/general/guides/authorization-guide/

/*
    Performs basic Authorization flow to acquire a Spotify OAuth2 token and refresh token.
    Should be used for long-running applications that require access only once.
    Opens a webbrowser and prompts the user to grant you access.
    @param scopes->The scopes of the token
*/
void Spotify::basicauthorize(std::string scopes) { 
    
    std::cout << "Starting Basic authorizing..." << std::endl;
    std::cout << "Validating scopes..." << std::endl;

    //Checks if scopes are valid
    if (validateScopes(scopes)) {
        std::cout << "Valid scopes" << std::endl;
    }
    else {
        std::cout << "Invalid scopes" << std::endl;
        return;
    }

    //A state is a random combination of characters that provides additional protection against threats like
    //cross-site request forgery.
    std::string state = utility::generateRandomText(8);

    //Creates the url
    std::string requestURL = "https://accounts.spotify.com/authorize?client_id=" + spotifyClientID
        + "&response_type=code"
        + "&redirect_uri=" + spotifyRedirectURI
        + "&state=" + state;
        + "&scope=" + scopes;

    //Converts to LPCWSTR so requestURL can be used in the shell
    std::wstring temp = std::wstring(requestURL.begin(), requestURL.end());
    LPCWSTR search = temp.c_str();


    //Opens the shell to open the browser and redirect to the requestURL
    std::cout << "Opening console..." << std::endl;
    ShellExecute(0, 0, search, 0, 0, SW_SHOW);

    std::cout << "Click the Authorize button then copy paste the URL of the redirect:" << std::endl;

    //Stores the URL in a variable
    std::string url;
    std::cin >> url;

    //Searches the string to find the code
    
    int32_t start = url.find("code");
    int32_t end = url.find("&state");

    //The code is stored in the variable tempToken
    std::string tempToken = url.substr(start + 5, end - start - 5);

    std::cout << "Trading code for OAuth2 token..." << std::endl;

    //Creating the POST data for the OAuth2 token request
    std::string postData = "client_id=" + spotifyClientID
        + "&grant_type=authorization_code"
        + "&code=" + tempToken
        + "&redirect_uri=https://www.google.com";

    //Creating the headers
    struct curl_slist* list = NULL;

    //The client ID and client secret needs to be in the form:
    //  client ID:client secret
    //and encoded in base64
    list = curl_slist_append(list, ("Authorization: Basic " + base64_encode(spotifyClientID + ":" + spotifyClientSecret)).c_str());

    //Performs POST request and saves the resulting token JSON in readBuffer
    std::string readBuffer=utility::performCURLPOST("https://accounts.spotify.com/api/token", postData, list);
    
    //std::cout << readBuffer << std::endl;
    
    //Offset to the start of the access token code in readBuffer
    int first = 17;

    //Sets the class's Token as the readBuffer's access token
    spotifyAuthenticityToken = readBuffer.substr(first, readBuffer.find("token_type") - first-3);
    
    //Finds the first index of the refresh token
    //The '16' is the offset from the first index of readBuffer.find("refresh_token")
    int refreshFirst = readBuffer.find("refresh_token")+16;

    //Sets the class's refresh token as the readBuffer's refresh token
    spotifyRefreshToken = readBuffer.substr(refreshFirst, readBuffer.length() - refreshFirst - 2);
    std::cout << "OAuth2 acquired!" << std::endl;

    /*Example token JSON
    {
    "access_token":"<code>",
    "token_type":"Bearer","expires_in":3600,
    "spotifyRefreshToken":"<code>"
    }*/

}

/*
    Uses the PCKE authorising process to acquire an OAuth2 token and refresh token and store it in the class.
    Should be used if it is unsafe to store your client secret in the app.
*/
void Spotify::authorizePCKE() {

    srand(time(NULL)); // random number generator
    std::string message;
    std::string codeChallenge;
    char c;
    int r;
    
    int num = rand() % 8 + 4;//Generates a number between 4->8

    //Generate random characters and appends to message. This is to ensure that the code_challenge is hashed
    //into different values each time


    for (int i = 0; i < num; i++)
    {
        r = rand() % 26;    // generate a random number
        c = 'a' + r;            // Convert to a character from a-z
        std::cout << c << std::endl;
        message += c;
    }
    
    codeChallenge = base64_encode(sha256(message));
    codeChallenge = codeChallenge.substr(0, codeChallenge.length() - 2);
    //Auth URL
    
    std::string query0 = "https://accounts.spotify.com/authorize?client_id="+ spotifyClientID 
        +"&response_type=code"
        +"&redirect_uri=https://www.google.com"
        //+"&state=e21392da45dbf4"
        +"&code_challenge="+ codeChallenge
        +"&code_challenge_method=S256";

    std::wstring temp = std::wstring(query0.begin(), query0.end());
    LPCWSTR search = temp.c_str();

    //Uses the shell to execute the search request
    ShellExecute(0, 0, search, 0, 0, SW_SHOW);
    std::cout << "Copy paste the url here:" << std::endl;
    std::string url;
    std::cin >> url;
    
    int32_t start = url.find("code");
    int32_t end = url.find("&state");
    std::string tempToken = url.substr(start + 5, end - start - 5);

    //int32_t end = url.length()-start;
    //std::string tempToken = url.substr(start + 5, end);

    std::string query1 = "client_id=" + spotifyClientID 
        +"&grant_type=authorization_code" 
        +"&code=" + tempToken 
        +"&redirect_uri=https://www.google.com"
        +"&code_verifier=" + codeChallenge;
    
    std::cout << "\n";
    std::cout << query0<< std::endl;
    std::cout << "\n";
    std::cout << query1 << std::endl;
    std::cout << "\n";
    

    CURL* curl;
    CURLcode res;

    //std::string basicAuth = "Authorization: Basic " + base64_encode(spotifyClientID + ":" + spotifyClientSecret);
    struct curl_slist* list = NULL;
    //list = curl_slist_append(list, "Accept: application/json");
    list = curl_slist_append(list, "content-type: application/x-www-form-urlencoded");

    //list = curl_slist_append(list, (basicAuth).c_str());

    //list = curl_slist_append(list, "Content-Type: application/json");

    curl_global_init(CURL_GLOBAL_ALL);
    
    curl = curl_easy_init();
    if (curl) {

        curl_easy_setopt(curl, CURLOPT_URL, "https://accounts.spotify.com/api/token");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query1.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));

        curl_easy_cleanup(curl);

        curl_global_cleanup();

    }
}

/*
    Performs a cURL request for user data
    @returns readBuffer->User data in JSON form
*/
std::string Spotify::getUserInfo() {
    
    //Creates storage unit for necessary headers
    struct curl_slist* list = NULL;
    
    //Appends the required headers
    list = curl_slist_append(list, "Accept: application/json");
    list = curl_slist_append(list, "Content-Type: application/json");
    list = curl_slist_append(list, ("Authorization: Bearer " + spotifyAuthenticityToken).c_str());

    //acquires user data and stores in variable readBuffer
    std::string readBuffer = utility::performCURLGET("https://api.spotify.com/v1/me", list);

    return readBuffer;

}

/*
 USER INFO
{
  "display_name" : "Roxx",
  "external_urls" : {
    "spotify" : "https://open.spotify.com/user/ki09vo7tt3rwgyrsma9lhjo4c"
  },
  "followers" : {
    "href" : null,
    "total" : 5
  },
  "href" : "https://api.spotify.com/v1/users/ki09vo7tt3rwgyrsma9lhjo4c",
  "id" : "ki09vo7tt3rwgyrsma9lhjo4c",
  "images" : [ {
    "height" : null,
    "url" : "https://i.scdn.co/image/ab6775700000ee855e3d7a922066af0672ddaf12",
    "width" : null
  } ],
  "type" : "user",
  "uri" : "spotify:user:ki09vo7tt3rwgyrsma9lhjo4c"
}
*/

/*
    Performs a cURL request for the user's display name
    @returns userInfo->user's display name
*/
std::string Spotify::getDisplayName(){
    std::string userInfo =getUserInfo();
    return userInfo.substr(22,userInfo.find('"',22)-22);
}

/*
    Performs a cURL request for the user's URL
    @returns userInfo->user's URL
*/
std::string Spotify::getUserURL(){
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"spotify\"") + 13;
    return userInfo.substr(first, userInfo.find('"',first)-first);
}

/*
    Performs a cURL request for the user's followers amount
    @returns followers->number of follows the user has
*/
int Spotify::getUserFollowers(){
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"total\"") + 10;
    std::string followers = userInfo.substr(first, userInfo.find('}', first) - first);
    return std::stoi(followers);
}

/*
    Performs a cURL request for the user's ID
    @returns userInfo->user's ID
*/
std::string Spotify::getUserID(){
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"id\"") + 8;
    return userInfo.substr(first, userInfo.find('"', first) - first);
}

/*
    Performs a cURL request for the user's profile picture source
    @returns userInfo->user's profile picture source
*/
std::string Spotify::getUserProfilePictureURL(){
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"url\"") + 9; 
    return userInfo.substr(first, userInfo.find('"', first) - first);
}

/*
    Performs a cURL request for the user's type
    @returns userInfo->user's type
*/
std::string Spotify::getUserType() {
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"type\"") + 10;
    return userInfo.substr(first, userInfo.find('"', first) - first);
}

/*
    Performs a cURL request for the user's URI
    @returns userInfo->user's URI
*/
std::string Spotify::getUserURI() {
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"uri\"") + 9;
    return userInfo.substr(first, userInfo.find('"', first) - first);
}


//PLAYER
std::string Spotify:: getUserPlaylists(int limit) {
    //Used for headers
    struct curl_slist* list = NULL;
    if (limit <= 0 || limit > 50) {
        return "INVALID LIMIT";
    }
    //Required headers
    list = curl_slist_append(list, "Accept: application/json");
    list = curl_slist_append(list, "Content-Type: application/json");
    list = curl_slist_append(list, ("Authorization: Bearer " + spotifyAuthenticityToken).c_str());

    //Buffer to write to
    std::string readBuffer = utility::performCURLGET("https://api.spotify.com/v1/me/playlists?"+std::to_string(limit), list);

    return readBuffer;
}


/*Getters*/

/*
    Gets spotifyAuthenticityToken
    @returns spotifyAuthenticityToken
*/
std::string Spotify::getToken() {
    return spotifyAuthenticityToken;
}

/*
    Gets spotifyClientID
    @returns spotifyClientID
*/
std::string Spotify::getClientID() {
    return spotifyClientID;
}

/*
    Gets spotifyClientSecret
    @returns spotifyClientSecret
*/
std::string Spotify::getClientSecret() {
    return spotifyClientSecret;
}

/*Setters*/

/*
    Sets spotifyAuthenticityToken
    @param userToken- new spotifyAuthenticityToken
*/
void Spotify::setToken(std::string userToken) {
    spotifyAuthenticityToken = userToken;
}

/*
    Sets spotifyClientID
    @param userspotifyClientID- new spotifyClientID
*/
void Spotify::setClientID(std::string userspotifyClientID) {
    spotifyClientID = userspotifyClientID;
}

/*
    Sets spotifyClientSecret
    @param userspotifyClientSecret- new spotifyClientSecret
*/
void Spotify::setClientSecret(std::string userspotifyClientSecret) {
    spotifyClientSecret = userspotifyClientSecret;
}


//Scopes

/*
source:https://developer.spotify.com/documentation/general/guides/scopes/
*/

/*
    Returns container containing all available spotify scopes
    @returns availableScopes
*/
std::vector<std::string> Spotify::spotifyScopes() {
    std::vector<std::string>availableScopes = {
        "ugc-image-upload",
        "playlist-modify-private",
        "playlist-read-private",
        "user-read-private",
        "user-read-playback-state",
        "user-library-modify",
        "user-read-playback-position",
        "app-remote-control",
        "user-read-recently-played",
        "user-modify-playback-state",
        "user-read-email",
        "user-follow-modify",
        "playlist-modify-public",
        "user-follow-read",
        "user-read-currently-playing",
        "playlist-read-collaborative",
        "user-library-read",
        "streaming",
        "user-top-read"
    };

    return availableScopes;
}

/*
    Validates inputted scopes.
    @param userScopes- scopes to validate(scopes must be seperated by a space)
*/
bool Spotify::validateScopes(std::string userScopes) {

    if (userScopes == "") {
        return true;
    }

    std::vector<std::string>scopes = spotifyScopes();

    int first = 0;

    while (userScopes.find(" ", first) != std::string::npos) {
        std::string message = userScopes.substr(first, userScopes.find(' ', first + 1) - first);

        message.erase(remove_if(message.begin(), message.end(), isspace), message.end());

        if (std::find(scopes.begin(), scopes.end(), message) != scopes.end()) {
            /* v contains x */
            first = userScopes.find(' ', first + 1);
        }
        else {
            /* v does not contain x */
            return false;
        }
    }
    
    return true;
}
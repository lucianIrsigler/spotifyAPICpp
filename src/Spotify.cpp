#include "Spotify.h"


void Spotify::basicauthorize(std::string scope) { 
    //Auth URL
    std::cout << "Starting Basic authorizing..." << std::endl;
    
    std::string state = utility::generateRandomText(8);
    std::string query0 = "https://accounts.spotify.com/authorize?client_id=" + spotifyClientID
        + "&response_type=code"
        + "&redirect_uri=" + spotifyRedirectURI
        + "&state=" + state;
        //+ "&scope=" + scope;

    std::cout << query0<<std::endl;
    std::wstring temp = std::wstring(query0.begin(), query0.end());
    LPCWSTR search = temp.c_str();
    std::cout << "Opening console..." << std::endl;
    //Uses the shell to execute the search request
    ShellExecute(0, 0, search, 0, 0, SW_SHOW);

    std::cout << "Click the Authorize button then copy paste the URL of the redirect:" << std::endl;
    std::string url;
    //std::string tempToken;
    std::cin >> url;

    int32_t start = url.find("code");
    int32_t end = url.find("&state");
    std::string tempToken = url.substr(start + 5, end - start - 5);

    std::cout << "Trading code for OAuth2 token..." << std::endl;

    std::string query1 = "client_id=" + spotifyClientID
        + "&grant_type=authorization_code"
        + "&code=" + tempToken
        + "&redirect_uri=https://www.google.com";


    struct curl_slist* list = NULL;
    list = curl_slist_append(list, ("Authorization: Basic " + base64_encode(spotifyClientID + ":" + spotifyClientSecret)).c_str());

    std::string readBuffer=utility::performCURLPOST("https://accounts.spotify.com/api/token", query1, list);
    
    std::cout << readBuffer << std::endl;
    int first = 17;

    spotifyAuthenticityToken = readBuffer.substr(first, readBuffer.find("token_type") - first-3);
    
    int refreshFirst = readBuffer.find("refresh_token")+16;
    spotifyRefreshToken = readBuffer.substr(refreshFirst, readBuffer.length() - refreshFirst - 2);
    std::cout << "OAuth2 acquired!" << std::endl;

    /*
    RES:{
    "access_token":"BQBs3C5No5hsbOEJXRT8RqLBdusDWhRYer2KALYH9ajvi4pjNAHkVGDKhIlIJDaRPJO_cDrzcib-L5ANp2juPQQSa2htNnoFT8dh5Wiqxgh2eMdrxGOWJapb6PIQQ578w1H1TrELxST1BLs-OTaiBBYqqwYSREBU65lcdQ",
    "token_type":"Bearer","expires_in":3600,
    "spotifyRefreshToken":"AQAzedgGlQFs5znzy7YxloZGFvZsO5WPYU5jDh1qOK7Z5qoNARdKg7ejiLrXUBl7NF6IZxrps3uaIki8VUEG1PulU1YVXoCWRi5C35opWb_vZmOMnbxJ6_AtNtTnAqNYkdg"}*/

}


/*
SOURCE -> https://developer.spotify.com/documentation/general/guides/authorization-guide/
Gets user to authorize a spotify token for the application

First a code_challenge is created from the sha256 algorithm.

Then the query string is created that needs the following info:
-client_id
-response_type
-redirect_uri
-state
-scope
-code_challenge
-code_challenge_method

After this query request is created- the browser is opened and redirected to this URL.

When the user authorizes the token- then browser redirects to google.com/{query1}{query2}
Where query1 is the auth token and query2 is the state

Then the following data is posted to https://accounts.spotify.com/api/token to trade the auth token
for an actual token:
-client_id
-grant_type
-code
-redirect_uri
-code_verifier

Upon a 200 response- a valid Spotify token can be accessed
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
Acquires the JSON for user data

@returns std::string->User data in JSON form*/

std::string Spotify::getUserInfo() {
    
    //Used for headers
    struct curl_slist* list = NULL;
    
    //Required headers
    list = curl_slist_append(list, "Accept: application/json");
    list = curl_slist_append(list, "Content-Type: application/json");
    list = curl_slist_append(list, ("Authorization: Bearer " + spotifyAuthenticityToken).c_str());

    //Buffer to write to
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


std::string Spotify::getDisplayName(){
    std::string userInfo =getUserInfo();
    return userInfo.substr(22,userInfo.find('"',22)-22);
}

std::string Spotify::getUserURL(){
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"spotify\"") + 13;
    return userInfo.substr(first, userInfo.find('"',first)-first);
}

int Spotify::getUserFollowers(){
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"total\"") + 10;
    std::string followers = userInfo.substr(first, userInfo.find('}', first) - first);
    
    return std::stoi(followers);
}

std::string Spotify::getUserID(){
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"id\"") + 8;
    return userInfo.substr(first, userInfo.find('"', first) - first);
}

std::string Spotify::getUserProfilePictureURL(){
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"url\"") + 9; 
    return userInfo.substr(first, userInfo.find('"', first) - first);
}

std::string Spotify::getUserType() {
    std::string userInfo = getUserInfo();
    int first = userInfo.find("\"type\"") + 10;
    return userInfo.substr(first, userInfo.find('"', first) - first);
}

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

/*getter for spotifyAuthenticityToken*/
std::string Spotify::getToken() {
    return spotifyAuthenticityToken;
}

/*getter for spotifyClientID*/
std::string Spotify::getClientID() {
    return spotifyClientID;
}

/*getter for spotifyClientSecret*/
std::string Spotify::getClientSecret() {
    return spotifyClientSecret;
}

/*Setters*/

/*setter for spotifyAuthenticityToken*/
void Spotify::setToken(std::string userToken) {
    spotifyAuthenticityToken = userToken;
}

/*setter for spotifyClientID*/
void Spotify::setClientID(std::string userspotifyClientID) {
    spotifyClientID = userspotifyClientID;
}

/*setter for spotifyClientSecret*/
void Spotify::setClientSecret(std::string userspotifyClientSecret) {
    spotifyClientSecret = userspotifyClientSecret;
}

//Scopes

/*
Returns avaiable scopes 
source:https://developer.spotify.com/documentation/general/guides/scopes/
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
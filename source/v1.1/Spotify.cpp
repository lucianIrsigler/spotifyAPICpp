#include "Spotify.h"

/**
    Spotify.cpp
    Purpose: Implementation of Spotify.h

    @author Lucian Irsigler
    @version 1.0 14/10/2021
*/


//AUTH source -> https://developer.spotify.com/documentation/general/guides/authorization-guide/
/*
    Performs basic Authorization flow to acquire a Spotify OAuth2 token and refresh token.
    Should be used for long-running applications that require access only once.
    Opens a webbrowser and prompts the user to grant you access.
    @param scopes->The scopes of the token
*/
void Spotify::basicauthorize(std::string scopes) { 
    
    //Checks if scopes are valid
    if (validateScopes(scopes)) {
        spotifyClassScopes = scopes;
    }
    else {
        throw spotifyException("Invalid scopes");
    }

    //A state is a random combination of characters that provides additional protection against threats like
    //cross-site request forgery.
    std::string state = utility::generateRandomText(8);

    //Creates the url
    std::string requestURL = "https://accounts.spotify.com/authorize?client_id=" + spotifyClientID
        + "&response_type=code"
        + "&redirect_uri=" + spotifyRedirectURI
        + "&state=" + state
        + "&scope=" + scopes;

    //std::cout << requestURL << std::endl;
    // 
    //Converts to LPCWSTR so requestURL can be used in the shell
    std::wstring temp = std::wstring(requestURL.begin(), requestURL.end());
    LPCWSTR search = temp.c_str();


    //Opens the shell to open the browser and redirect to the requestURL
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

    std::cout << "\n\n" << readBuffer << "\n\n" << std::endl;
    //std::cout << readBuffer << std::endl;
    
    //Offset to the start of the access token code in readBuffer
    int first = 17;

    //Sets the class's Token as the readBuffer's access token
    spotifyAuthenticityToken = readBuffer.substr(first, readBuffer.find("token_type") - first-3);
    
    //Finds the first index of the refresh token
    //The '16' is the offset from the first index of readBuffer.find("refresh_token")
    int refreshFirst = readBuffer.find("refresh_token")+16;

    //Sets the class's refresh token as the readBuffer's refresh token
    spotifyRefreshToken = readBuffer.substr(refreshFirst, readBuffer.find('"',refreshFirst)-refreshFirst);

    //std::cout << spotifyRefreshToken << std::endl;

    /*Example token JSON
    {
    "access_token":"<code>",
    "token_type":"Bearer","expires_in":3600,
    "spotifyRefreshToken":"<code>",
    "scope":"<scopes>"
    }*/

}

/*
    Uses the PCKE authorising process to acquire an OAuth2 token and refresh token and store it in the class.
    Should be used if it is unsafe to store your client secret in the app.
*/
/*
void Spotify::authorizePCKE() {

    srand(static_cast<unsigned int>time(NULL)); // random number generator
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
*/

/*
    Performs a cURL request for user data
    @returns readBuffer->User data in JSON form
*/
std::string Spotify::getUserInfo() {
    
    //acquires user data and stores in variable readBuffer
    std::string readBuffer = utility::performCURLGET("https://api.spotify.com/v1/me", spotifyAuthenticityToken);
    
    try{
        utility::checkConditions(readBuffer);
        return readBuffer;
    }
    catch (const spotifyException& error) {
        return error.what();
    }
}

/*
    Performs a cURL request for the user's display name
    @returns userInfo->user's display name
*/
std::string Spotify::getDisplayName(){
    std::string userInfo =getUserInfo();
    std::cout << userInfo << std::endl;
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


//Playlist

/*
    Searches for a user and returns their playlists.
    Required scopes:playlist-read-private playlist-read-collaborative
    @param userID->userID to search for
    @param limit->number of playlists to return. Max is 50 and minimum 1
    @param offset->How many playlists to skip initially
    @returns User's playlist in JSON format
*/
std::string Spotify::getSearchedUserPlaylists(std::string userID, int limit, int offset) {
    //https://developer.spotify.com/console/get-playlists/
    //playlist-read-private playlist-read-collaborative
   
    if ( utility::isLimitsAndOffsetInvalid(limit, offset)) {
        throw spotifyException("ERROR: Invalid limit/offset");
    }
    std::string url = "https://api.spotify.com/v1/users/" + userID + "/playlists?" + std::to_string(limit) + "&offset" + std::to_string(offset);

    std::string readBuffer = utility::performCURLGET(url, spotifyAuthenticityToken);

    try {
         utility::checkConditions(readBuffer);
        return readBuffer;
    }
    catch (const spotifyException& error) {
        return error.what();
    }
}


/*
    Gets the user associated with the token's playlists
    @param limit->number of playlists to get
    @param offset->number of playlists to skip initially
    @returns User's playlist in JSON format
*/
std::string Spotify::getUserPlaylists(int limit, int offset){
    //https://developer.spotify.com/console/get-current-user-playlists/

    /*if (spotifyClassScopes.find("playlist-read-private") == std::string::npos)
    {
        throw spotifyException("ERROR:'playlist-read-private' scope is required");
    }*/

    if ( utility::isLimitsAndOffsetInvalid(limit, offset)) {
        throw spotifyException("ERROR: Invalid limit/offset");
    }

    //Buffer to write to
    std::string readBuffer = utility::performCURLGET("https://api.spotify.com/v1/me/playlists?" + std::to_string(limit), spotifyAuthenticityToken);

    try {
         utility::checkConditions(readBuffer);
        return readBuffer;
    }
    catch (const spotifyException& error) {
        return error.what();
    }
}

std::vector<std::string> getUserPlaylistsNames() {

}
/*
    Gets a playlist
    @param playlistID->playlistID to search for
    @param market-> market to search for
    @param fields->fields to search for
    @returns Playlist info

*/
std::string Spotify::getPlaylist(std::string playlistID, std::string market, std::string fields) {
    //https://developer.spotify.com/console/get-playlist/

    std::string url = "https://api.spotify.com/v1/playlists/"
        + playlistID
        + "?market=" + market
        + "fields" + fields;
    

    std::string readBuffer = utility::performCURLGET(url, spotifyAuthenticityToken);

    try {
         utility::checkConditions(readBuffer);
        return readBuffer;
    }
    catch (const spotifyException& error) {
        return error.what();
    }
}

/*
    Retrieves the playlist display picture
    @param playlistID->playlist to search for
    @returns url of the playlist cover
*/
std::string Spotify::getPlaylistCover(std::string playlistID) {
    //https://developer.spotify.com/console/get-playlist-images/

    std::string url = "https://api.spotify.com/v1/playlists/" + playlistID + "/images";


    std::string readBuffer = utility::performCURLGET(url, spotifyAuthenticityToken);

    try {
         utility::checkConditions(readBuffer);
        return readBuffer;
    }
    catch (const spotifyException& error) {
        return error.what();
    }
}

/*
    Gets a playlist's songs.
    Required scopes:playlist-read-private
    @param playlistID->playlist to search for
    @param market->market of songs to find
    @param fields->fields to search for
    @param limit->number of songs to search for. Max is 50
    @param offset->How many playlists are skipped initially
    @returns the playlist's items.
*/
std::string Spotify::getPlaylistItems(std::string playlistID, std::string market, std::string fields, int limit, int offset) {
    //https://developer.spotify.com/console/get-playlist-tracks/

    if ( utility::isLimitsAndOffsetInvalid(limit, offset)) {
        throw spotifyException("ERROR: Invalid limit/offset");
    }

    std::string url = "https://api.spotify.com/v1/playlists/" + playlistID + "/tracks?";

    if (market != "") {
        url += "market=" + market;
    }
    if (fields != "") {
        url = "&fields=" + fields;
    }

    url += "&limit=" + std::to_string(limit);
    url+="&offset=" + std::to_string(offset);

    std::string readBuffer = utility::performCURLGET(url, spotifyAuthenticityToken);

    try {
         utility::checkConditions(readBuffer);
        return readBuffer;
    }
    catch (const spotifyException& error) {
        return error.what();
    }
}

/*
    Creates a playlist.
    Required scopes:playlist-modify-public playlist-modify-private
    @param userID->User to create the playlist for
    @param name-> name of playlist
    @param description->Description of playlist
    @param isPublic->The playlist's public status
*/
void Spotify::createPlaylist(std::string userID, std::string name, std::string description, bool isPublic) {
    //https://developer.spotify.com/console/post-playlists/

    //playlist-modify-public playlist-modify-private
    if (name.length() == 0) {
        throw spotifyException("Name too short");
    }
    std::string publicString;
    isPublic ? publicString = "true" : publicString = "false";

    std::vector<std::string>areas = {"name",name,"description",description,"public",publicString};

    ///{0:1,2:3,4,5}
    //{"name":"","description":"","public":true}
    std::string temp = json::convertToJSONString("{\"0\":\"1\",\"2\":\"3\",\"4\":5}", areas);

    std::string JSONobject = json::convertToJSONObject(temp);
   
    std::string readBuffer =utility::performCURLPOST("https://api.spotify.com/v1/users/" + userID + "/playlists", JSONobject, spotifyAuthenticityToken);
    
    try {
         utility::checkConditions(readBuffer);
        std::cout << readBuffer << std::endl;
    }
    catch (const spotifyException& error) {
        std::cout << error.what() << std::endl;
    }
}

/*
    Adds a song to a playlist
    Required scopes:playlist-modify-public playlist-modify-private
    @param playlistID->playlist to search for
    @param URI->song to add. Leave empty if you are adding via the vector
    @param position->Position to add the songs into the Playlist
    @param URIS->songs to add
*/
void Spotify::addItemToPlaylist(std::string playlistID, std::string URI, int position, std::vector<std::string> URIS) {
    //https://developer.spotify.com/console/post-playlist-tracks/

    //playlist-modify-public playlist-modify-private  

    // {\"0\" : [\"1\",\"2\",\"3\"...\"n\"]}

    URIS.insert(URIS.begin(), "uris");

    std::string JSONQuery = "{\"0\" : [";
    size_t counter = 1;

    while (counter < URIS.size()-1) {
        std::cout << counter << std::endl;
        JSONQuery += "\""+std::to_string(counter)+"\",";
        counter += 1;
    }

    JSONQuery += "\"" + std::to_string(counter++) + "\"]}";


    std::string temp = json::convertToJSONString(std::move(JSONQuery), URIS);

   
    
    /*std::string JSONString = "{\"uris\": [";

    for (int i = 0; i < URIS.size(); i++) {
        JSONString += "\"" + URIS[i] + "\",";
    }
    
    JSONString += "\"" + URIS[URIS.size() - 1] + "\""+"]}";*/

    std::string JSONobject = json::convertToJSONObject(temp);


    std::string postData = "position" + std::to_string(position);

    if (URI != "") {
        postData += "&uris=" + URI;
    }

    std::string url = "https://api.spotify.com/v1/playlists/" + playlistID + "/tracks?" + postData;

    std::string readBuffer = utility::performCURLPOST(url, JSONobject, spotifyAuthenticityToken);
    
    std::cout << readBuffer << std::endl;
}

/*
    Deletes a song to a playlist
    Required scopes:playlist-modify-public playlist-modify-private
    @param playlistID->playlist to search for
    @param URIS->songs to delete
*/
void Spotify::deleteItemFromPlaylist(std::string playlistID, std::vector<std::string> URIS) {
    //https://developer.spotify.com/console/delete-playlist-tracks/

    //playlist-modify-public playlist-modify-private

    std::string JSONString = "{ \"tracks\": [";

    for (size_t i = 0; i < URIS.size() - 1; i++) {
        JSONString += "{ \"uri\": \"" + URIS[i] + "\" },";
    }

    JSONString += "{ \"uri\": \"" + URIS[URIS.size()-1] + "\" }" + "] }";


    std::string JSONobject = json::convertToJSONObject(JSONString);

    std::string url = "https://api.spotify.com/v1/playlists/" + playlistID + "/tracks";
    std::string readBuffer = utility::performCURLPOST(url, JSONobject, spotifyAuthenticityToken);

    std::cout << readBuffer << std::endl;
    //{ "tracks": [{ "uri": "spotify:track:4iV5W9uYEdYUVa79Axb7Rh" },{ "uri": "spotify:track:1301WleyT98MSxVHPZCA6M" }] }
}   
    //{1:[{2:3},{2:3}]}

//{"uris": ["spotify:track:4iV5W9uYEdYUVa79Axb7Rh","spotify:track:1301WleyT98MSxVHPZCA6M", "spotify:episode:512ojhOuo1ktJprKbVcKyQ"]}
//{1:[2,3,4]}

/*
    Updates the playlist item
    Required scopes:playlist-modify-public playlist-modify-private
    @param playlistID->playlist to search for
    @param URI->song to add. Leave empty if you are adding via the vector
    @param position->Position to add the songs into the Playlist
    @param URIS->songs to add
*/
void Spotify::updatePlaylistItems(std::string playlistID, std::string URIs, std::string requestBody) {
    //https://developer.spotify.com/console/put-playlist-tracks/

    //playlist-modify-public playlist-modify-private
    
}

/*
    x
    Required scopes:playlist-modify-public playlist-modify-private
    @param URIS->songs to add
*/
void Spotify::changePlaylistDetails(std::string playlistID, std::string name, std::string description, bool isPublic) {
    //https://developer.spotify.com/console/put-playlist/
    if (name.length() == 0) {
        throw spotifyException("Name too short");

    }
    std::string publicString;
    isPublic ? publicString = "true" : publicString = "false";

    std::vector<std::string>areas = { "name",name,"description",description,"public", publicString };

    std::string temp = json::convertToJSONString("{\"0\":\"1\",\"2\":\"3\",\"4\":5}", areas);

    std::string JSONobject = json::convertToJSONObject(temp);
    
    std::string url = "https://api.spotify.com/v1/playlists/" + playlistID;

    std::string readBuffer = utility::performCURLPUT(url, JSONobject, spotifyAuthenticityToken);
}

/*

*/

//Player

/*

*/
std::string Spotify:: getUserRecentPlaying(int limit) {
    //https://developer.spotify.com/console/get-recently-played/
    
    //user-read-recently-played

    //acquires user data and stores in variable readBuffer
    std::string readBuffer = utility::performCURLGET("https://api.spotify.com/v1/me/player/recently-played", spotifyAuthenticityToken);
    std::cout << readBuffer << std::endl;
    try {
         utility::checkConditions(readBuffer);
        return readBuffer;
    }
    catch (const spotifyException& error) {
        return error.what();
    }
}

/*

*/
std::string Spotify:: getUserPlaybackState() {
    //https://developer.spotify.com/console/get-user-player/
    // 
    //user-read-playback-state


    //acquires user data and stores in variable readBuffer
    std::string readBuffer = utility::performCURLGET("https://api.spotify.com/v1/me/player/recently-played", spotifyAuthenticityToken);

    return readBuffer;
}

/*

*/
void Spotify::transferUserPlayback() {

}

/*

*/
std::string Spotify::getAvialableDevices() {
    //https://developer.spotify.com/console/get-users-available-devices/
    //user-read-playback-state

    std::string readBuffer = utility::performCURLGET("https://api.spotify.com/v1/me/player/devices", spotifyAuthenticityToken);


    return readBuffer;
}

/*

*/
std::string Spotify::getUserCurrentPlaying(){
    //user-read-currently-playing
    // 
    //acquires user data and stores in variable readBuffer
    std::string readBuffer = utility::performCURLGET("https://api.spotify.com/v1/me/player/currently-playing", spotifyAuthenticityToken);

    try {
         utility::checkConditions(readBuffer);
        return readBuffer;
    }
    catch (const spotifyException& error) {
        return error.what();
    }

}

/*

*/
void Spotify::resumeUserPlayback(){
    //https://developer.spotify.com/console/put-play/


}

/*

*/
void Spotify::pauseUserPlayback(std::string deviceID){
    //https://developer.spotify.com/console/put-pause/

    //user-modify-playback-state

    std::string readBuffer = utility::performCURLPUT("https://api.spotify.com/v1/me/player/pause", "", spotifyAuthenticityToken);
    
    try {
         utility::checkConditions(readBuffer);
    }
    catch (const spotifyException& error) {
        std::cout<<error.what()<<std::endl;
    }
}

/*

*/
void Spotify::skipToNextTrack(std::string deviceID){
    //https://developer.spotify.com/console/post-next/

    //user-modify-playback-state

    std::string readBuffer = utility::performCURLPOST("https://api.spotify.com/v1/me/player/next", "", spotifyAuthenticityToken);

    try {
         utility::checkConditions(readBuffer);
    }
    catch (const spotifyException& error) {
        std::cout << error.what() << std::endl;
    }

}

/*

*/
void Spotify::skipToPreviousTrack(std::string deviceID){
    //https://developer.spotify.com/console/post-previous/

    //user-modify-playback-state
    
    std::string readBuffer = utility::performCURLPOST("https://api.spotify.com/v1/me/player/previous", "", spotifyAuthenticityToken);

    try {
         utility::checkConditions(readBuffer);
    }
    catch (const spotifyException& error) {
        std::cout << error.what() << std::endl;
    }
}

/*

*/
void Spotify::seekToPositionCurrentTrack(){

}

/*

*/
void Spotify::setRepeatOnPlayback(std::string state, std::string deviceID){
    //https://developer.spotify.com/console/put-repeat/

    /*track will repeat the current track.
    context will repeat the current context.
    off will turn repeat off.*/

    if (state == "track" || state == "context" || state == "off") {
        std::string url = "https://api.spotify.com/v1/me/player/repeat?state=" + state;

        if (deviceID != "") {
            url+="&device_id" + deviceID;
        }

        std::string readBuffer = utility::performCURLPUT(url, "", spotifyAuthenticityToken);
        std::cout << readBuffer << std::endl;
        try {
            utility::checkConditions(readBuffer);
        }
        catch (const spotifyException& error) {
            std::cout << error.what() << std::endl;
        }
    }
    else {
        throw spotifyException("Invalid state");
    }
}

/*

*/
void Spotify::setVolumeOnPlayback(int volume,std::string deviceID){
    //https://developer.spotify.com/console/put-volume/

    if ((0 > volume) || (volume > 100)) {
        throw spotifyException("Invalid volume.");
    }

    //user-modify-playback-state


    std::string url = "https://api.spotify.com/v1/me/player/volume?volume_percent" + std::to_string(volume) + "&device_id=" + deviceID;

    std::string readBuffer = utility::performCURLPUT(url, "", spotifyAuthenticityToken);

    try {
         utility::checkConditions(readBuffer);
    }
    catch (const spotifyException& error) {
        std::cout << error.what() << std::endl;
    }
}

/*

*/
void Spotify::toggleShuffleOnPlayback(bool shuffle, std::string deviceID){
    // https://developer.spotify.com/console/put-shuffle/

    /*
    true- shuffle
    false- does not shuffle
    */

    //user-modify-playback-state


    std::string state;

    shuffle ? state = "true" : state = "false";

    std::string url = "https://api.spotify.com/v1/me/player/shuffle?state=" + state + "&&device_id=" + deviceID;

    std::string readBuffer = utility::performCURLPUT(url, "", spotifyAuthenticityToken);
    std::cout << readBuffer << std::endl;
    try {
         utility::checkConditions(readBuffer);
    }
    catch (const spotifyException& error) {
        std::cout << error.what() << std::endl;
    }

}

/*

*/
void Spotify::addSongToUserQueue(std::string URI, std::string deviceID){

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

*/
bool Spotify::isValidScopes(std::string scope) {
    std::vector<std::string>scopes = spotifyScopes();
    if (std::find(scopes.begin(), scopes.end(), scope) != scopes.end()) {
        return true;
    }
    
    return false;
    
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

/*
    Trades refresh token for another OAuth2 token. Upon the exchange- the API does not provide another refresh token
*/
void Spotify::refreshToken() {
    //Creating the POST data for the OAuth2 token request
    
    std::string postData = "&grant_type=refresh_token&refresh_token=" + spotifyRefreshToken;

    //Creating the headers
    struct curl_slist* list = NULL;

    //The client ID and client secret needs to be in the form:
    //  client ID:client secret
    //and encoded in base64
    list = curl_slist_append(list, ("Authorization: Basic " + base64_encode(spotifyClientID + ":" + spotifyClientSecret)).c_str());

    //Performs POST request and saves the resulting token JSON in readBuffer
    std::string readBuffer = utility::performCURLPOST("https://accounts.spotify.com/api/token", postData, list);
    
    //std::cout << readBuffer << std::endl;
    // 
    //Offset to the start of the access token code in readBuffer
    int first = 17;

    //Sets the class's Token as the readBuffer's access token
    spotifyAuthenticityToken = readBuffer.substr(first, readBuffer.find("token_type") - first - 3);

    /*
    //Finds the first index of the refresh token
    //The '16' is the offset from the first index of readBuffer.find("refresh_token")
    int refreshFirst = readBuffer.find("refresh_token") + 16;

    //Sets the class's refresh token as the readBuffer's refresh token
    spotifyRefreshToken = readBuffer.substr(refreshFirst, readBuffer.find('"', refreshFirst) - refreshFirst);*/
    spotifyRefreshToken = "";
}

# Purpose of this project
This project creates a wrapper for the spotify API

# How to use
In the "source" folder in this repo- there contains a "include" and "libs" folder.

The "include/spotify" folder contains the files you need to add as a "include directory" in project properties

The "libs" folder contains the static .lib file you need to link against your project.

# API calls
The API endpoints can be found [here](https://developer.spotify.com/documentation/web-api)
This wrapper covers all the API calls for the following:
1) Albums
2) Artists
3) Player
4) Playlist
5) Followers
6) Users
7) Authorization with the OAuth2 protocal

# Event loop of an API call
An API call is executed in the following way:
1) Define the API endpoint URL
2) Do the revelent HTTP call to that URL(POST/PUT/DELETE/GET...)
3) Check for errors and log the error

An API call might require specific scopes. the *enum/scopes.h* file provides an enum for scopes. A scope defined in this enum can correspond to a relevent API call group
Meaning, for example, the developer can call scopes::user to get all the scopes required to make any of the user API calls work

# Token
The spotify API uses tokens. These tokens have to be required via the OAuth2 protocal with very specific steps and specific HTTP calls.
The procress for acquiring the token can be found [here](https://developer.spotify.com/documentation/web-api/tutorials/code-flow).

Additionally, the wrapper provides a basic way for user's to acquire an authorization code. Additionally, each code comes with a refresh token. This refresh token is used to acquire another authorization code when the current one expires.

The wrapper provides token functionaility by providing the ability to 1) authorize with scopes and 2) refresh the token.
Once the token has been acquired, it gets written to a text file in the same directory as the exe. When the app restarts, it will search for the text file and extract the tokens.

The wrapper can automatically reacquire another token when the following triggers occur:
1) The text files for the tokens are not present
2) An API call is made to an API endpoint that requires no endpoint, such as https://api.spotify.com/v1/me
3) The length of the token must be correct/be atleast a minimum length.

# Design philosophy 
The project uses inheritance and derived classes.

# Dependencies
This project depends on the [cURL](https://github.com/curl/curl) library and the [jsonCPP](https://github.com/open-source-parsers/jsoncpp) library.

# TODO list
* Implement CMake files
* Add more testing
* Add more API calls

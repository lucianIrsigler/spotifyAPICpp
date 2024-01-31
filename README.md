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

An API call might require specific scopes. the *scopes.h* file provides an enum for scopes. A scope defined in this enum can correspond to a relevent API call group
Meaning, for example, the 
# Dependencies
This project depends on the [cURL](https://github.com/curl/curl) library and the [jsonCPP](https://github.com/open-source-parsers/jsoncpp) library.

# TODO list
* Implement CMake files
* Add more testing
* Add more API calls
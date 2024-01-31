#pragma once
#include <string>
#include <curl/curl.h>

/*
    Writes HTTP request to a variable and returns it. Used for cURL methods
*/
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

/*
    Performs a GET HTTP request on the spotify API
    @param website->website to search
    @param token->valid Bearer token for the HTTP header
    @returns JSON response body
*/
static const std::string performCURLGET(std::string website, std::string token) {
    CURL* curl;//Initilizes a cURL
    CURLcode res;

    struct curl_slist* list = NULL;

    list = curl_slist_append(list, "Accept: application/json");
    list = curl_slist_append(list, "Content-Type: application/json");
    list = curl_slist_append(list, ("Authorization: Bearer " + token).c_str());

    //Buffer to write to
    std::string readBuffer;

    //Initilizes the cURL request
    curl = curl_easy_init();
    if (curl) {

        //Set options

        //Sets URL
        curl_easy_setopt(curl, CURLOPT_URL, website.c_str());

        //Sets writer function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        //Sets where to write the data to
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        //Sets headers
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

        //Performs HTTP GET request
        res = curl_easy_perform(curl);

        //Cleanups process
        curl_easy_cleanup(curl);

        return readBuffer;
    }
    else {
        return "ERROR: curl failed";
    }
}


/*
    Performs a POST HTTP request on the spotify API
    @param website->website to search
    @param POSTdata-> POST data to send to the website
    @param token->valid Bearer token for the HTTP header
    @returns JSON response body
*/
static const std::string performCURLPOST(std::string website, std::string POSTdata, std::string token) {
    CURL* curl;
    CURLcode res;

    struct curl_slist* list = NULL;

    list = curl_slist_append(list, "Accept: application/json");
    list = curl_slist_append(list, "Content-Type: application/json");
    list = curl_slist_append(list, ("Authorization: Bearer " + token).c_str());


    std::string readBuffer;
    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, website.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, POSTdata.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
            return "ERROR: HTTP POST request failed";
        }
        curl_easy_cleanup(curl);

        curl_global_cleanup();

        return readBuffer;
    }
    else {
        return "ERROR: curl failed";
    }
}


/*
    Performs a PUT HTTP request on the spotify API
    @param website->website to search
    @param POSTdata-> POST data to send to the website
    @param token->valid Bearer token for the HTTP header
    @returns JSON response body
*/
static const std::string performCURLPOST(std::string website, std::string POSTdata, struct curl_slist* list) {
    CURL* curl;
    CURLcode res;


    std::string readBuffer;
    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, website.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, POSTdata.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
            return "ERROR: HTTP POST request failed";
        }
        curl_easy_cleanup(curl);

        curl_global_cleanup();

        return readBuffer;
    }
    else {
        return "ERROR: curl failed";
    }
}


/*
    Performs a PUT HTTP request on the spotify API
    @param website->website to search
    @param POSTdata-> POST data to send to the website
    @param token->valid Bearer token for the HTTP header
    @returns JSON response body
*/
static const std::string performCURLPUT(std::string website, std::string POSTdata, std::string token) {
    CURL* curl;
    CURLcode res;

    //Used for headers
    struct curl_slist* list = NULL;

    list = curl_slist_append(list, "Accept: application/json");
    list = curl_slist_append(list, "Content-Type: application/json");
    list = curl_slist_append(list, ("Authorization: Bearer " + token).c_str());

    std::string readBuffer;
    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, website.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, POSTdata.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
            return "ERROR: HTTP POST request failed";
        }
        curl_easy_cleanup(curl);

        curl_global_cleanup();

        return readBuffer;
    }
    else {
        return "ERROR: curl failed";
    }
}


/*
    Performs a DELETE HTTP request on the spotify API
    @param website->website to search
    @param POSTdata-> POST data to send to the website
    @param token->valid Bearer token for the HTTP header
    @returns JSON response body
*/
static const std::string performCURLDELETE(std::string website, std::string POSTdata, std::string token) {
    CURL* curl;
    CURLcode res;

    //Used for headers
    struct curl_slist* list = NULL;

    list = curl_slist_append(list, "Accept: application/json");
    list = curl_slist_append(list, "Content-Type: application/json");
    list = curl_slist_append(list, ("Authorization: Bearer " + token).c_str());

    std::string readBuffer;
    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, website.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, POSTdata.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
            return "ERROR: HTTP POST request failed";
        }
        curl_easy_cleanup(curl);

        curl_global_cleanup();

        return readBuffer;
    }
    else {
        return "ERROR: curl failed";
    }
}
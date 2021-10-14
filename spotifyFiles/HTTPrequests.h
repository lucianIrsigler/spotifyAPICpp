#pragma once
#include <curl/curl.h>
#include <string>

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

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


std::string makeRequest(std::string website)
{
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, website.c_str()); //get page
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); //creates writer function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer); //Writes to a buffer
        res = curl_easy_perform(curl);//performs HTTP GET request and writes to buffer
        curl_easy_cleanup(curl); //Performs clean up
        return readBuffer;
    }
    return "error";
}
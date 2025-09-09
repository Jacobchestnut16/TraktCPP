//
// Created by Jacob on 9/5/25.
//

#include "trakt_api.h"
#include <curl/curl.h>
#include <config.h>
#include <iostream>
#include "json.hpp"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}



nlohmann::json makeRequestNoAuth(const std::string &endpoint, const TraktConfig &config) {
    std::cout << "Make a Request to: " << endpoint << "\n" << std::flush;
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, endpoint.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        curl_slist *headers = NULL;

        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "trakt-api-version: 2");
        std::string authHeader = "trakt-api-key: " + config.clientId;
        headers = curl_slist_append(headers, authHeader.c_str());
        headers = curl_slist_append(headers, "User-Agent: BetterWatchlist/1.0.0"); //technically needed

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);


        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);


        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n" << std::flush;
        } else {
            long http_code = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            std::cerr << "HTTP status: " << http_code << "\n" << std::flush;
            if (http_code == 401) {
                std::cerr
                << "Trakt API Keys attempted \n { \n"
                << " \"client_id\" : \""
                <<config.clientId
                << "\"\n } \n"
                << std::flush;
            }
        }
    }else {
        std::cerr << "Curl either could not be initialized or is not installed." << "\n" << std::flush;
    }

    std::cout << "response: " << readBuffer << "\n" << std::flush;
    try {
        nlohmann::json response = nlohmann::json::parse(readBuffer);
        if (response.contains("results")) {
            return response["results"];  // just the array
        } else {
            return response;             // fallback: return full JSON if "results" missing
        }
    } catch (const std::exception& e) {
        std::cerr << "JSON parse error: " << e.what() << "\n" << std::flush;
        return nlohmann::json{};
    }
}


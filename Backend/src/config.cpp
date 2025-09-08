//
// Created by Jacob on 9/5/25.
//

#include "config.h"

#include <fstream>
#include <iostream>
#include "json.hpp"


TraktConfig loadConfig(const std::string& path) {
    TraktConfig config;

    // open file
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Cannot open config file: " << path << "\n";
        return config;
    }

    try {
        nlohmann::json j;
        file >> j;

        if (!j.is_object()) {
            std::cerr << "Invalid JSON in config file: " << path << "\n";
            return config;
        }

        // extract values safely
        if (j.contains("client_id"))     config.clientId     = j["client_id"].get<std::string>();
        if (j.contains("client_secret")) config.clientSecret = j["client_secret"].get<std::string>();
        if (j.contains("tmdb_bearer"))   config.tmdb_bearer  = j["tmdb_bearer"].get<std::string>();
        if (j.contains("host"))          config.host         = j["host"].get<std::string>();
        if (j.contains("port"))          config.port         = j["port"].get<int>();

    } catch (const std::exception& e) {
        std::cerr << "Error parsing config file: " << e.what() << "\n";
    }

    return config;
}
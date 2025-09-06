//
// Created by Jacob on 9/5/25.
//

#ifndef BACKEND_CONFIG_H
#define BACKEND_CONFIG_H
#include <QString>

struct TraktConfig {
    QString clientId;
    QString clientSecret;
    QString tmdb_bearer;
    std::string host;
    int port;
    // QString accessToken; // future: store/retrieve access token
};

// Load configuration from JSON file
TraktConfig loadConfig(const QString &path);


#endif //BACKEND_CONFIG_H
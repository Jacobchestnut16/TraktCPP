//
// Created by Jacob on 9/5/25.
//

#ifndef BACKEND_TRAKT_API_H
#define BACKEND_TRAKT_API_H
#include <QJsonArray>
#include <config.h>

QString const BASE = "https://api.trakt.tv/";

QJsonArray makeRequestNoAuth(const QString &endpoint, const TraktConfig &config);

// TraktAPI trakt(cfg);


#endif //BACKEND_TRAKT_API_H
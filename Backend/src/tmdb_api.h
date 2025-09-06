//
// Created by Jacob on 9/5/25.
//

#ifndef BACKEND_TMDB_API_H
#define BACKEND_TMDB_API_H

#include <QJsonArray>
#include <config.h>

#include "json.hpp"
#include "routes.h"


// https://api.themoviedb.org/3/movie/popular
QString const TMDB_BASE = "https://api.themoviedb.org/3";

QJsonArray makeTMDBRequest(const QString &endpoint, const TraktConfig &config);


#endif //BACKEND_TMDB_API_H
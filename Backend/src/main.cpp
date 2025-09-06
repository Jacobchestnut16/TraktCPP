#include <QCoreApplication>
#include <QFile>

#include <config.h>
#include <trakt_api.h>
#include <tmdb_api.h>
#include <routes.h>
#include <data_store.h>
#include <QJsonDocument>

#include "httplib.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);


    // Initialize the config
    TraktConfig config = loadConfig("../config/config.json");


    // Make a call
    httplib::Server svr;
    Routes routes;

    // QJsonArray trendingMovies = makeRequestNoAuth(BASE+"movies/trending", config);
    // QJsonArray trendingShows = makeRequestNoAuth(BASE+"shows/trending", config);
    // json moviesJson = json::parse(QString(QJsonDocument(trendingMovies).toJson()).toStdString());
    // json showsJson = json::parse(QString(QJsonDocument(trendingShows).toJson()).toStdString());



    // https://api.themoviedb.org/3/{movie/tv}/popular
    registerThreeRoutes(routes, "/popular",
        qJsonArrayToJson(makeTMDBRequest(TMDB_BASE+"/movie/popular", config)),
        qJsonArrayToJson(makeTMDBRequest(TMDB_BASE+"/tv/popular", config)));


    // https://api.themoviedb.org/3/{movie/tv}/top_rated
    registerThreeRoutes(routes, "/top_rated",
    qJsonArrayToJson(makeTMDBRequest(TMDB_BASE+"/movie/top_rated", config)),
    qJsonArrayToJson(makeTMDBRequest(TMDB_BASE+"/tv/top_rated", config)));

    // https://api.themoviedb.org/3/movie/now_playing
    // https://api.themoviedb.org/3/movie/upcoming
    // https://api.themoviedb.org/3/tv/airing_today


    // https://api.trakt.tv/{movies/shows}/played/monthly


//     QJsonArray movies_played = makeRequestNoAuth(TMDB_BASE+"/movies/played/monthly", config);
//     QJsonArray showss_played = makeRequestNoAuth(TMDB_BASE+"/shows/played/monthly", config);
//
//
//     // todo: transfer everything from trakt to
//     // https://api.themoviedb.org/3/movie/{id} or https://api.themoviedb.org/3/tv/{id}
//     // then three routes
//
//     registerThreeRoutes(routes, "/most_played",
// qJsonArrayToJson(makeRequestNoAuth(TMDB_BASE+"/movies/played/monthly", config)),
// qJsonArrayToJson(makeRequestNoAuth(TMDB_BASE+"/shows/played/monthly", config)));
//
//
//     // https://api.trakt.tv/movies/watched/monthly
//     registerThreeRoutes(routes, "/most_watched",
// qJsonArrayToJson(makeRequestNoAuth(TMDB_BASE+"/movies/watched/monthly", config)),
// qJsonArrayToJson(makeRequestNoAuth(TMDB_BASE+"/shows/watched/monthly", config)));

    // recommended → user-personalized picks.
    // upcoming → unreleased but scheduled.
    // underrated → high ratings but low watch counts.
    // todo: get films watched or get individuals top high rated film
    // todo: use to get recommended and grab high rated films
    // todo: add a threshold if there aren't enough low watch counts with high ratings drop (add to a drop json before dropping)
    // todo: finally if the list is under 10 films re-add random drops to fulfill this list
    // similar → items related to a given movie/show.
    // history → user’s watch log.
    // analytics → aggregated stats like avg rating, completion %, binge patterns.
    // curated → from all watch lists get 3-6 recommendations per film
    // todo: get a combined list of all watchlist' data
    // todo: get 3-6 recommendations per film based on rating 3 no rating 6 highest rating
    // todo: propose: considerations to shorten the list [newest films, most popular, oldest films]


    routes.bindToServer(svr);
    std::cout << "Server running on http://localhost:" << config.port << "\n";
    svr.listen(config.host, 8080);

    return 0;
}

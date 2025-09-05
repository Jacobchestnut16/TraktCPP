#include <QCoreApplication>
#include <QNetworkReply>
#include <QJsonObject>
#include <QDebug>
#include <QCoreApplication>
#include <QFile>

#include <config.h>
#include <trakt_api.h>
#include <routes.h>
#include <data_store.h>

#include "httplib.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);


    // Initialize the config
    TraktConfig config = loadConfig("../config/config.json");

    // // 2. Initialize Trakt API handler
    // TraktAPI trakt(cfg);
    //
    // // 3. Initialize data store (optional cache)
    // DataStore store;
    //
    // // 4. Create HTTP server
    // httplib::Server svr;
    //
    // // 5. Register API routes
    // registerRoutes(svr, trakt, store);


    // Make a call
    QJsonArray trending = makeRequestNoAuth(BASE+"movies/trending", config);

    // print the results
    for(const QJsonValue &val : trending){
        QJsonObject obj = val.toObject();
        QJsonObject movie = obj["movie"].toObject();
        qDebug() << "Title:" << movie["title"].toString()
                 << "Year:" << movie["year"].toInt()
                 << "Trakt URL:" << movie["ids"].toObject()["slug"].toString();
    }

    httplib::Server svr;


    std::cout << "Server running on http://localhost:" << config.port << "\n";
    svr.listen(config.host, config.port);
    return 0;
}

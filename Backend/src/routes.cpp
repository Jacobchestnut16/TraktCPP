//
// Created by Jacob on 9/5/25.
//

#include "routes.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QCoreApplication>
#include "json.hpp"




 // Writes a path endpoint /trending/moives and stores the json blob
void Routes::registerEndpoint(const std::string& path, const json& staticData) {
    handlers["/api"+path] = [staticData](const httplib::Request&) {
        return staticData;
    };
}

 // binds the endpoints to the server to be reached by GET headers
void Routes::bindToServer(httplib::Server& svr) {
    for (auto& [path, handler] : handlers) {
        svr.Get(path.c_str(), [handler](const httplib::Request& req, httplib::Response& res) {
            json result = handler(req);
            res.set_content(result.dump(), "application/json");
        });
    }
}

 // Clean up qjson
json qJsonArrayToJson(QJsonArray array) {
    return json::parse(QString(QJsonDocument(array).toJson()).toStdString());
}

 // Register three types of routes at once
void registerThreeRoutes(Routes& routes, const std::string& path, const json& movieData, const json& showData) {
    routes.registerEndpoint(path + "/movies", movieData);
    routes.registerEndpoint(path + "/shows", showData);

    routes.registerEndpoint(path, json{
    {"movies", movieData},
    {"shows",  showData}
    });
}
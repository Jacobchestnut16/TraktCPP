//
// Created by Jacob on 9/5/25.
//

#include "trakt_api.h"

#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QCoreApplication>
#include <config.h>

QJsonArray makeRequestNoAuth(const QString &endpoint, const TraktConfig &config) {
    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl(endpoint.toUtf8()));
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("trakt-api-version", "2");
    request.setRawHeader("trakt-api-key", config.clientId.toUtf8());

    QEventLoop loop;
    QJsonArray result;

    QObject::connect(&manager, &QNetworkAccessManager::finished, [&](QNetworkReply *reply){
        if(reply->error() != QNetworkReply::NoError){
            qWarning() << "Error:" << reply->errorString();
        } else {
            const QByteArray data = reply->readAll();
            QJsonDocument json = QJsonDocument::fromJson(data);
            result = json.array();
        }
        reply->deleteLater();
        loop.quit();
    });

    manager.get(request);
    loop.exec(); // Wait for request to finish

    return result;
}
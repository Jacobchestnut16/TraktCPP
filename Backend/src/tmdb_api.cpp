//
// Created by Jacob on 9/5/25.
//

#include "tmdb_api.h"

#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QCoreApplication>
#include <config.h>
#include <QJsonObject>
#include <routes.h>

QJsonArray makeTMDBRequest(const QString &endpoint, const TraktConfig &config) {
    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl(endpoint.toUtf8()));
    request.setRawHeader("Accept", "application/json");
    QString token = config.tmdb_bearer.trimmed();
    QByteArray authHeader = "Bearer " + token.toUtf8();
    request.setRawHeader("Authorization", authHeader);

    QEventLoop loop;
    QJsonArray result; // this will hold the "results" array

    QObject::connect(&manager, &QNetworkAccessManager::finished,
        [&](QNetworkReply *reply) {
            int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            QString reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
            std::cout << "Calling TMDB" << std::endl;
            qDebug() << "HTTP status:" << statusCode << reason;

            QByteArray data = reply->readAll();

            if (reply->error() != QNetworkReply::NoError) {
                qWarning() << "Error:" << reply->errorString();
                qWarning() << "Body:" << data;
            } else {
                qDebug() << "Raw response:" << data.left(500);

                // Parse the JSON
                QJsonParseError parseError;
                QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
                if (parseError.error != QJsonParseError::NoError) {
                    qWarning() << "JSON parse error:" << parseError.errorString();
                } else if (doc.isObject()) {
                    QJsonObject obj = doc.object();
                    if (obj.contains("results") && obj.value("results").isArray()) {
                        result = obj.value("results").toArray(); // assign the results array
                    } else {
                        qWarning() << "Response JSON has no 'results' array.";
                    }
                } else {
                    qWarning() << "Response JSON is not an object.";
                }
            }

            reply->deleteLater();
            loop.quit();
        });

    manager.get(request);
    loop.exec(); // Wait for request to finish

    return result;
}




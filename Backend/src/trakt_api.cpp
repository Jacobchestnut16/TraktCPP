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
#include <routes.h>

QJsonArray makeRequestNoAuth(const QString &endpoint, const TraktConfig &config) {
    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl(endpoint.toUtf8()));
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("trakt-api-version", "2");
    request.setRawHeader("trakt-api-key", config.clientId.c_str());
    request.setRawHeader("User-Agent", "BetterWatchlist/1.0.0"); // required


    QEventLoop loop;
    QJsonArray result;

    QObject::connect(&manager, &QNetworkAccessManager::finished,
        [&](QNetworkReply *reply) {
            int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            QString reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
            std::cout << "Calling Trakt" <<  std::endl;
            qDebug() << "HTTP status:" << statusCode << reason;

            if (reply->error() != QNetworkReply::NoError) {
                qWarning() << "Error:" << reply->errorString();
                qWarning() << "Body:" << reply->readAll();
            } else {
                QByteArray data = reply->readAll();
                qDebug() << "Raw response:" << data.left(500); // first 500 bytes
                QJsonParseError parseError;
                QJsonDocument json = QJsonDocument::fromJson(data, &parseError);
                if (parseError.error != QJsonParseError::NoError) {
                    qWarning() << "JSON parse error:" << parseError.errorString();
                } else if (json.isArray()) {
                    result = json.array();
                } else {
                    qWarning() << "Response not a JSON array.";
                }
            }

            reply->deleteLater();
            loop.quit();
        });

    manager.get(request);
    loop.exec(); // Wait for request to finish

    return result;
}




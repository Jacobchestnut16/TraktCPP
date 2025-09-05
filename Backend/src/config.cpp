//
// Created by Jacob on 9/5/25.
//

#include "config.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>


TraktConfig loadConfig(const QString &path) {
    TraktConfig config;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Cannot open config file:" << path;
        return config;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (!doc.isObject()) {
        qWarning() << "Invalid JSON in config file:" << path;
        return config;
    }

    QJsonObject obj = doc.object();
    config.clientId = obj.value("client_id").toString();
    config.clientSecret = obj.value("client_secret").toString();
    config.host = obj.value("host").toString().toStdString();
    config.port = obj.value("port").toInt();

    return config;
}
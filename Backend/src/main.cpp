#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QCoreApplication>
#include <QFile>

struct TraktConfig {
    QString clientId;
    QString clientSecret;
    // QString accessToken; // todo: add a method to retrieve and access a accessToken from Trakt
};

TraktConfig loadConfig(const QString &path) {
    // Open the file
    QFile file(path);
    //set the env var
    TraktConfig config;

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Cannot open config file:" << path;
        return config;
    }

    // read the json structure
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject obj = doc.object();

    // assign the vars
    config.clientId = obj.value("client_id").toString();
    config.clientSecret = obj.value("client_secret").toString();

    return config;
}

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

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // Read the Keys file
    TraktConfig config = loadConfig("../config/config.json");

    QString base = "https://api.trakt.tv/";

    // Make a call
    QJsonArray trending = makeRequestNoAuth(base+"movies/trending", config);

    // print the results
    for(const QJsonValue &val : trending){
        QJsonObject obj = val.toObject();
        QJsonObject movie = obj["movie"].toObject();
        qDebug() << "Title:" << movie["title"].toString()
                 << "Year:" << movie["year"].toInt()
                 << "Trakt URL:" << movie["ids"].toObject()["slug"].toString();
    }
    // todo:
    // todo:
    // todo:
    // todo:
    // todo:
    // todo:
    // todo:
    // todo:
    // todo:

    return 0;
}
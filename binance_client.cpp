#include "binance_client.h"

binance_client::binance_client(QObject *parent) : QObject(parent)
{
    time_manager = new QNetworkAccessManager(this);

    connect(time_manager, &QNetworkAccessManager::finished, this, &binance_client::reply_time_manager);

    QUrl url(QString(API_URL)+QString(TIME_V1));
    QNetworkRequest request;
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    request.setUrl(url);

    time_manager->get(request);
}

void binance_client::reply_time_manager(QNetworkReply* reply){
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    QJsonDocument jsondoc = QJsonDocument::fromJson(data);
    if (!jsondoc.isNull()) {
        if (jsondoc.isObject()) {
            QJsonObject obj = jsondoc.object();

            qDebug() << obj["serverTime"].toString();
            qDebug() << obj["ap_time"].toString();
            qDebug() << obj["block_time"].toString();
        }
    }

    reply->deleteLater();
}

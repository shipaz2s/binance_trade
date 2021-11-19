#ifndef BINANCE_CONNECT_H
#define BINANCE_CONNECT_H

#include <QtCore>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>

//#define API_URL "https://api.binance.com/api"
#define API_URL "https://dex.binance.org/api"
#define TIME_V1 "/v1/time"

class binance_client : public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager *time_manager;

    void reply_time_manager(QNetworkReply* reply);

public:
    explicit binance_client(QObject *parent = nullptr);


signals:

};

#endif // BINANCE_CONNECT_H

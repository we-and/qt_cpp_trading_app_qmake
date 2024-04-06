#include "financedatamanager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

FinanceDataManager::FinanceDataManager(QObject *parent) : QObject(parent) {
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &FinanceDataManager::onNetworkReply);
}

void FinanceDataManager::queryFinanceData(const QString &symbol) {
    QUrl url(QString("https://your-api-endpoint.com/symbol=%1").arg(symbol));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    // Replace "Your-Api-Key" with your actual API key
    request.setRawHeader("X-API-KEY", "Your-Api-Key");
    manager->get(request);
}

void FinanceDataManager::onNetworkReply(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << "Network error:" << reply->errorString();
        return;
    }

    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    auto data = parseFinanceData(document);
    emit dataReady(data);
}

QList<QCandlestickSet *> FinanceDataManager::parseFinanceData(const QJsonDocument &document) {
    QList<QCandlestickSet *> sets;
    // Your parsing logic here. This is a placeholder implementation.
    return sets;
}

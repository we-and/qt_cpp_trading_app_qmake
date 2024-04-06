#ifndef FINANCEDATAMANAGER_H
#define FINANCEDATAMANAGER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtCharts/QCandlestickSet>

#include <QtWidgets>
#include <QtCharts>

#include <QtCharts/QCandlestickSeries>

#include <QtCharts/QCandlestickSet>
#include <QtCharts/QChartView>

class FinanceDataManager : public QObject {
    Q_OBJECT
public:
    explicit FinanceDataManager(QObject *parent = nullptr);
    void queryFinanceData(const QString &symbol);

signals:
    void dataReady(const QList<QCandlestickSet *> &data);

private slots:
    void onNetworkReply(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    QList<QCandlestickSet *> parseFinanceData(const QJsonDocument &document);
};

#endif // FINANCEDATAMANAGER_H

#ifndef TICKERTABLEMANAGER_H
#define TICKERTABLEMANAGER_H

#include <QObject>
#include <QTableWidget>
#include <QStringList>

class TickerTableManager : public QObject
{
    Q_OBJECT

public:
    explicit TickerTableManager(QTableWidget *table, QObject *parent = nullptr);
    void addTicker(const QString &ticker, double sellPrice, double buyPrice, double change, double changePercent, const QString &dateUpdated);
    void clearTable();

private:
    QTableWidget *table;
    QStringList headers = {"Ticker", "Sell Price", "Buy Price", "Change", "Change in %", "Date Updated"};
};

#endif // TICKERTABLEMANAGER_H

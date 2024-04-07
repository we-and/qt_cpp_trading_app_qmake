#include "TickerTableManager.h"
#include "QtWidgets/qheaderview.h"

#include <QObject>
#include <QTableWidget>
#include <QStringList>

TickerTableManager::TickerTableManager(QTableWidget *table, QObject *parent) : QObject(parent), table(table)
{
    if (this->table) {
        this->table->setColumnCount(headers.size());
        this->table->setHorizontalHeaderLabels(headers);
        this->table->horizontalHeader()->setStretchLastSection(true);
    }

}

void TickerTableManager::addTicker(const QString &ticker, double sellPrice, double buyPrice, double change, double changePercent, const QString &dateUpdated)
{
    if (!table) return;

    int row = table->rowCount();
    table->insertRow(row);
    table->setItem(row, 0, new QTableWidgetItem(ticker));
    table->setItem(row, 1, new QTableWidgetItem(QString::number(sellPrice, 'f', 2)));
    table->setItem(row, 2, new QTableWidgetItem(QString::number(buyPrice, 'f', 2)));
    table->setItem(row, 3, new QTableWidgetItem(QString::number(change, 'f', 2)));
    table->setItem(row, 4, new QTableWidgetItem(QString::number(changePercent, 'f', 2) + "%"));
    table->setItem(row, 5, new QTableWidgetItem(dateUpdated));
}

void TickerTableManager::clearTable()
{
    if (!table) return;

    table->clearContents();
    table->setRowCount(0);
}

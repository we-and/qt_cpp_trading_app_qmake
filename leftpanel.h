#ifndef LEFTPANEL_H
#define LEFTPANEL_H

#include "QtCharts/qcandlestickset.h"
#include "mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>

class LeftPanel : public QWidget
{
    Q_OBJECT

public:
    explicit LeftPanel(QWidget *parent = nullptr, QMdiArea * mdiArea=nullptr);
    void addButton(const QString &buttonText);
    void setupLeftPanel(QWidget *parent,QVBoxLayout * layout);
QList<QCandlestickSet *>      generateRealisticCandlestickData(int N);
signals:
    void tickerTableCellClicked(int row, int column);
    void tickerCategoryButtonClicked(int row, int column);
public slots:
    void onTickerCategoryButtonClicked();
       void onTickerTableCellClicked(int row, int column);
private:
//    QWidget *midPanel;

    QVBoxLayout *layout;
    MainWindow * mainWindow;
    QMdiArea * mdiArea;
};

#endif // LEFTPANEL_H

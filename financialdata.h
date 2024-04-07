#ifndef FINANCIALCHART_H
#define FINANCIALCHART_H

#include <QtWidgets>
#include <QtCharts>

//using namespace QtCharts;

class FinancialChart : public QWidget
{
    Q_OBJECT

public:
    explicit FinancialChart(QWidget *parent = nullptr);
    void addCandlestickData(const QList<QCandlestickSet *> &dataSets, const QStringList dateLabels);
    void setTitle(QString title_);
private:
    QString title;
    QChartView *chartView;
    QCandlestickSeries *series;
    QChart *chart;
};

#endif // FINANCIALCHART_H

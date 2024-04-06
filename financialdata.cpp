#include "financialdata.h"


FinancialChart::FinancialChart(QWidget *parent) : QWidget(parent), series(new QCandlestickSeries(this)), chart(new QChart())
{
    series->setName("Sample Candlestick Series");
    series->setIncreasingColor(Qt::green);
    series->setDecreasingColor(Qt::red);

    chart->addSeries(series);
    chart->setTitle("Financial Data");
    chart->createDefaultAxes();
    chart->legend()->hide();

    chartView = new QChartView(chart, this);
    chartView->setRubberBand(QChartView::RectangleRubberBand); // Enable rectangular zooming
    chartView->setRenderHint(QPainter::Antialiasing);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);
}

void FinancialChart::addCandlestickData(const QList<QCandlestickSet *> &dataSets, const QStringList dateLabels)
{
    for (auto *set : dataSets) {
        series->append(set);
    }



    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(dateLabels);
    chart->setAxisX(axisX, series);


    // Assuming dataSets is not empty, adjust axis
    chart->axes(Qt::Horizontal).first()->setRange(0, dataSets.size());
    qreal minPrice = std::numeric_limits<qreal>::max(), maxPrice = std::numeric_limits<qreal>::lowest();
    for (const auto *set : dataSets) {
        minPrice = qMin(minPrice, set->low());
        maxPrice = qMax(maxPrice, set->high());
    }
    chart->axes(Qt::Vertical).first()->setRange(minPrice, maxPrice);
}

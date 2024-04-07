#include "mainwindow.h"
#include <QMdiSubWindow>
#include <QTextEdit>
#include <QMdiSubWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDateTime>
#include <QRandomGenerator>
#include <QDate>
#include <QtCharts/QCandlestickSeries>
#include "LeftPanel.h"
#include "financialdata.h"
#include "stylesbutton.h"
#include <QtCharts/QCandlestickSet>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <TickerTableManager.h>
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{


    std::cout << "MAINWINDOW"<<std::endl;
    // Set up the central widget and its layout
    centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // Set up the MDI area
    mdiArea = new QMdiArea;

    // Set up the left panel
    leftPanel = new LeftPanel(this,mdiArea);
    //setupLeftPanel(leftPanel);


   // connect(leftPanel, &LeftPanel::tickerTableCellClicked, this, &MainWindow::onTickerTableCellClicked);

    // Add both panels to the main layout
    mainLayout->addWidget(leftPanel, 1); // The second parameter can adjust the relative size
    mainLayout->addWidget(mdiArea, 3);


    // Set the central widget
    setCentralWidget(centralWidget);
    std::cout << "MAINWINDOW done"<<std::endl;

}



MainWindow::~MainWindow()
{
}




QList<QCandlestickSet *> generateRealisticCandlestickData(int count) {
    QList<QCandlestickSet *> sets;
    //connect(table, &QTableWidget::cellClicked, this, &MainWindow::onTickerTableCellClicked);

    // Starting parameters
    qreal lastClose = 100.0; // Starting stock price
    qreal trend = 0.2; // Slight upward trend, can be negative for downward

    for (int i = 0; i < count; ++i) {
        qreal open = lastClose + (QRandomGenerator::global()->generateDouble() * 2.0 - 1.0 + trend);
        qreal close = open + (QRandomGenerator::global()->generateDouble() * 2.0 - 1.0 + trend);
        qreal high = qMax(open, close) + QRandomGenerator::global()->generateDouble() * 5.0;
        qreal low = qMin(open, close) - QRandomGenerator::global()->generateDouble() * 5.0;

        // Ensure the low is never below zero
        low = qMax(0.0, low);

        sets.append(new QCandlestickSet(open, high, low, close, i));

        lastClose = close; // Update lastClose for the next day
    }

    return sets;
}




void MainWindow::onTickerTableCellClicked(int row, int column)
{
    Q_UNUSED(row)
    Q_UNUSED(column)
//    QTableWidgetItem *item = table->item(row, 0); // 0 for the first column
  {//  if (item != nullptr) {
    //    QString value = item->text();
      //  qDebug() << "Clicked value in the first column:" << value;

    // Create candlestick series
    QCandlestickSeries *series = new QCandlestickSeries();

    QList<QCandlestickSet *> candlesticks;
    series->setName("Random Data");
    series->setIncreasingColor(Qt::green);
    series->setDecreasingColor(Qt::red);

    qreal highestValue = std::numeric_limits<qreal>::lowest(); // or -std::numeric_limits<qreal>::max()
    qreal lowestValue = std::numeric_limits<qreal>::max();


    int N=100;
  candlesticks =generateRealisticCandlestickData(N);
    // Generate 500 random candlesticks
    for (int i = 0; i < N; ++i) {
     QCandlestickSet *  set = candlesticks[i];
        if (set->high() > highestValue) highestValue = set->high();
        if (set->low() < lowestValue) lowestValue = set->low();
    }

    // Create the chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Candlestick Chart");
//    chart->createDefaultAxes();


    QStringList dateLabels;

    QDate startDate = QDate::currentDate().addDays(-500); // Starting 500 days ago
    for (int i = 0; i < N; ++i) {
        dateLabels << startDate.addDays(i).toString("yyyy-MM-dd");
    }

    // Setup X-axis
    QBarCategoryAxis *axisX = new QBarCategoryAxis();

  //  QBarCategoryAxis *axisX = new QBarCategoryAxis();


//    axisX->append("Date"); // Add categories as needed
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Setup Y-axis
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(lowestValue, highestValue); // Set to the range of your data
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Create an instance of FinancialChart
    FinancialChart *financialChart = new FinancialChart(this);
    financialChart->setTitle("AA");
    // Add data to the chart
    financialChart->addCandlestickData(candlesticks,dateLabels);



    // Create the chart view
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Create a subwindow and set the chart view as its widget
    QMdiSubWindow *chartSubWindow = new QMdiSubWindow;
    // Display the chart, e.g., by adding it to the layout of the central widget
    chartSubWindow->setWidget(financialChart);

    //    chartSubWindow->setWidget(chartView);
    chartSubWindow->resize(400, 300);
    mdiArea->addSubWindow(chartSubWindow);

    chartSubWindow->show();
    }
}

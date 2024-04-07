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
#include "financialdata.h"


#include <QtCharts/QCandlestickSet>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set up the central widget and its layout
    centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // Set up the left panel
    leftPanel = new QWidget;
    setupLeftPanel(leftPanel);
//    leftLayout = new QVBoxLayout(leftPanel);
  //  leftPanel->setLayout(leftLayout);

    // Add buttons to the left panel
  //  QPushButton *button1 = new QPushButton("Indices");
    //connect(button1, &QPushButton::clicked, this, &MainWindow::onButtonClicked); // Connect the signal to the slot

//      leftLayout->addWidget(button1);
    // Add more buttons as needed

    // Set up the MDI area
    mdiArea = new QMdiArea;

    // Add both panels to the main layout
    mainLayout->addWidget(leftPanel, 1); // The second parameter can adjust the relative size
    mainLayout->addWidget(mdiArea, 3);

    // Set the central widget
    setCentralWidget(centralWidget);
}


void MainWindow::setupLeftPanel(QWidget *parent)
{

    QStringList financialInstruments;
    financialInstruments << "Indices"
                         << "FX"
                         << "Cryptocurrencies"
                         << "Commodities"
                         << "ETF"
                         << "Bonds"
                         << "Options";

    QStringList financialInstruments2;
    financialInstruments2 << "Account"
                         << "Settings"
                         << "Account"
;


    QVBoxLayout *panelLayout = new QVBoxLayout(parent);

    // Top buttons layout
    QVBoxLayout *topLayout = new QVBoxLayout();
    for (int i = 1; i <= 5; ++i) {
        QPushButton *button = new QPushButton( financialInstruments[i]   , parent);
        connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked); // Connect the signal to the slot
        topLayout->addWidget(button);
    }

    // Bottom buttons layout
    QVBoxLayout *bottomLayout = new QVBoxLayout();
    for (int i = 1; i <= 2; ++i) {
        QPushButton *button = new QPushButton(financialInstruments2[i], parent);
        //  QPushButton *button1 = new QPushButton("Indices");
        connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked); // Connect the signal to the slot

        bottomLayout->addWidget(button);
    }

    // Spacer item
    QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    // Add top layout, spacer, and bottom layout to the panel layout
    panelLayout->addLayout(topLayout);
    panelLayout->addItem(spacer);
    panelLayout->addLayout(bottomLayout);
}

MainWindow::~MainWindow()
{
}




QList<QCandlestickSet *> generateRealisticCandlestickData(int count) {
    QList<QCandlestickSet *> sets;

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


void MainWindow::onButtonClicked()
{
    // Create a new subwindow
    QMdiSubWindow *subWindow = new QMdiSubWindow;

    // Create the table widget
    QTableWidget *table = new QTableWidget(30, 6); // 30 rows and 5 columns
    QStringList headers = {"Ticker","Sell Price", "Buy Price", "Change", "Change in %", "Date Updated"};
    table->setHorizontalHeaderLabels(headers);

    // Sample ticker names
    QStringList tickerNames = {"AAPL", "GOOGL", "MSFT", "AMZN", "TSLA", "FB", "BRK.A", "V", "JNJ", "WMT"};


    // Fill the table with dummy data
    for (int row = 0; row < 30; ++row) {
        int tickerIndex = QRandomGenerator::global()->bounded(tickerNames.size());
        table->setItem(row, 0, new QTableWidgetItem(tickerNames.at(tickerIndex)));

        table->setItem(row, 1, new QTableWidgetItem(QString::number(100.0 + QRandomGenerator::global()->bounded(50.0) + QRandomGenerator::global()->bounded(100) / 100.0)));
        table->setItem(row, 2, new QTableWidgetItem(QString::number(100.0 + QRandomGenerator::global()->bounded(50.0) + QRandomGenerator::global()->bounded(100) / 100.0)));
        table->setItem(row, 3, new QTableWidgetItem(QString::number(QRandomGenerator::global()->bounded(-50, 51) + QRandomGenerator::global()->bounded(100) / 100.0)));
        table->setItem(row, 4, new QTableWidgetItem(QString::number(QRandomGenerator::global()->bounded(-5, 11) + QRandomGenerator::global()->bounded(100) / 100.0)));
        table->setItem(row, 5, new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")));
    }

    connect(table, &QTableWidget::cellClicked, this, &MainWindow::onCellClicked);


    // Resize columns to fit content
    table->resizeColumnsToContents();

    subWindow->setWidget(table);

    mdiArea->addSubWindow(subWindow);

    subWindow->show();}




void MainWindow::onCellClicked(int row, int column)
{
    Q_UNUSED(row)
    Q_UNUSED(column)

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

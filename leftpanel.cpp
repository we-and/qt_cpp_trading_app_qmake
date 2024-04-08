#include "LeftPanel.h"
#include <QPushButton>
#include <QStyle>

#include "QtCharts/qbarcategoryaxis.h"
#include "QtCharts/qcandlestickseries.h"
#include "QtCharts/qchart.h"
#include "QtCharts/qchartview.h"
#include "QtCharts/qvalueaxis.h"
#include "QtWidgets/qmdisubwindow.h"
#include "TickerTableManager.h"
#include "financialdata.h"
#include "leftpanel.h"
#include "searchbutton.h"
#include "stylesbutton.h"

#include <QTableWidgetItem>
#include <QDateTime>
#include <QRandomGenerator>
#include <iostream>
LeftPanel::LeftPanel(QWidget *parent,QMdiArea * mdiArea) : QWidget(parent)
{
    std::cout << "LEFT PANEL"<<std::endl;
    this->mainWindow=qobject_cast<MainWindow*>(parent);
    this->mdiArea=mdiArea;
    layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0); // Remove padding around the layout
    layout->setSpacing(0); // Remove spacing between buttons

    setupLeftPanel(this,layout);
    // Optional: Set the panel's style to ensure no additional padding or margins
    setStyleSheet("LeftPanel { padding: 0px; margin: 0px;   background-color:green; }");
}

void LeftPanel::addButton(const QString &buttonText)
{
    std::cout << "Add button"<<std::endl;
    QPushButton *button = new QPushButton(buttonText, this);
    button->setStyleSheet("text-align: l    eft; border: none;");
    layout->addWidget(button);

    // Stretch to align buttons to top and bottom
    if (layout->count() == 1) { // First button
        layout->addStretch(1); // Add stretch after the first button
    }
}


void LeftPanel::setupLeftPanel(QWidget *parent,QVBoxLayout * layout)
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


     QVBoxLayout *topLayout = new QVBoxLayout();
    SearchButtonWidget * search = new SearchButtonWidget();
    topLayout->addWidget(search);



    for (int i = 1; i <= 5; ++i) {
        StyledButton *button = new StyledButton( financialInstruments[i]   , parent);
        connect(button, &QPushButton::clicked, this, &LeftPanel::onTickerCategoryButtonClicked); // Connect the signal to the slot
        topLayout->addWidget(button);
    }

    // Bottom buttons layout
    QVBoxLayout *bottomLayout = new QVBoxLayout();
    for (int i = 1; i <= 2; ++i) {
        StyledButton *button = new StyledButton(financialInstruments2[i], parent);
        //  QPushButton *button1 = new QPushButton("Indices");
        connect(button, &QPushButton::clicked, this, &LeftPanel::onTickerCategoryButtonClicked); // Connect the signal to the slot

        bottomLayout->addWidget(button);
    }

    // Spacer item
    QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    // Add top layout, spacer, and bottom layout to the panel layout
    layout->addLayout(topLayout);
    layout->addItem(spacer);
    layout->addLayout(bottomLayout);
}


void LeftPanel::onTickerCategoryButtonClicked(){
    // Create a new subwindow
    QMdiSubWindow *subWindow = new QMdiSubWindow;

  //  QWidget * mid= new QWidget();
//    QVBoxLayout * layout=new QVBoxLayout(mid);

    // Create the table widget
    QTableWidget *table = new QTableWidget(30, 6); // 30 rows and 5 columns
    TickerTableManager *manager = new TickerTableManager(table, this);
    // Example of adding a ticker

    // Sample ticker names
    QStringList tickerNames = {"AAPL", "GOOGL", "MSFT", "AMZN", "TSLA", "FB", "BRK.A", "V", "JNJ", "WMT"};

    QStringList headers = {"Ticker","Sell Price", "Buy Price", "Change", "Change in %", "Date Updated"};
    table->setHorizontalHeaderLabels(headers);

    for (int row = 0; row < 5; ++row) {
        QString h=tickerNames.at(row);
        double sell=(100.0 + QRandomGenerator::global()->bounded(50.0) + QRandomGenerator::global()->bounded(100) / 100.0);
        double buy=(100.0 + QRandomGenerator::global()->bounded(50.0) + QRandomGenerator::global()->bounded(100) / 100.0);
        double change=(QRandomGenerator::global()->bounded(-50, 51) + QRandomGenerator::global()->bounded(100) / 100.0);
        double changepc=(QRandomGenerator::global()->bounded(-50, 51) + QRandomGenerator::global()->bounded(100) / 100.0);
        QString time=QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
        manager->addTicker(h, sell,buy, change,changepc,time);
    }




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

    // Inside LeftPanel, when setting up the table
    connect(table, &QTableWidget::cellClicked, this, &LeftPanel::tickerTableCellClicked);

    connect(this, &LeftPanel::tickerTableCellClicked, this, &LeftPanel::onTickerTableCellClicked);

//    connect(table, &QTableWidget::cellClicked, this, &MainWindow::onTickerTableCellClicked);

    QWidget * w = new QWidget(this);
    QVBoxLayout * layout = new QVBoxLayout(w);

    QLabel * title=new QLabel(this);
    title->setText("TITLE");
    layout->addWidget(title);

    layout->addWidget(table);
    // Resize columns to fit content
    table->resizeColumnsToContents();
    //subWindow->setWidget(table);

    this->mainWindow->midPanel->show();

    mainWindow->midPanel->layout()->addWidget(w);
    //    this->mdiArea->addSubWindow(subWindow);
  //  subWindow->show();
}




void LeftPanel::onTickerTableCellClicked(int row, int column)
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
        candlesticks =this->generateRealisticCandlestickData(N);
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

QList<QCandlestickSet *> LeftPanel::generateRealisticCandlestickData(int count) {
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








#include "LeftPanel.h"
#include <QPushButton>
#include <QStyle>

#include "QtWidgets/qmdisubwindow.h"
#include "TickerTableManager.h"
#include "leftpanel.h"
#include "stylesbutton.h"

#include <QTableWidgetItem>
#include <QDateTime>
#include <QRandomGenerator>
#include <iostream>
LeftPanel::LeftPanel(QWidget *parent,QMdiArea * mdiArea) : QWidget(parent)
{
    std::cout << "LEFT PANEL"<<std::endl;

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


   // QVBoxLayout *panelLayout = new QVBoxLayout(parent);
   // setCentralWidget(panelLayout);
    // Top buttons layout
    QVBoxLayout *topLayout = new QVBoxLayout();
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

//    connect(table, &QTableWidget::cellClicked, this, &MainWindow::onTickerTableCellClicked);


    // Resize columns to fit content
    table->resizeColumnsToContents();

    subWindow->setWidget(table);

    this->mdiArea->addSubWindow(subWindow);

    subWindow->show();
}


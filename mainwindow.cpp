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
#include "midpanel.h"
#include "topwidget.h"
#include <QtCharts/QCandlestickSet>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <TickerTableManager.h>
#include <iostream>
#include <QTabWidget>
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QWidget * mm = new QWidget(this);
    QVBoxLayout *m = new QVBoxLayout(mm);

    m->setContentsMargins(0, 0,0, 0); // Adjust margins as needed
    m->setSpacing(0);

    // Create the QTabWidget
    tabWidget = new CustomTabWidget(this);
tabWidget->tabBar()->hide();



    std::cout << "MAINWINDOW"<<std::endl;
    // Set up the central widget and its layout
    QWidget * firstTabWidget = new QWidget(this);

    QHBoxLayout *mainLayout = new QHBoxLayout(firstTabWidget);
    mainLayout->setContentsMargins(0, 0,0, 0); // Adjust margins as needed
    mainLayout->setSpacing(0);

    // Set up the MDI area
    mdiArea = new QMdiArea;

    qDebug() << "BUILD MIDPANEL";
    this->midPanel = new MidPanel(this,mdiArea);


    // Set up the left panel
    leftPanel = new LeftPanel(this,mdiArea);
    //setupLeftPanel(leftPanel);



    mainLayout->addWidget(leftPanel, 1); // The second parameter can adjust the relative size
    mainLayout->addWidget(midPanel, 1); // The second parameter can adjust the relative size
    mainLayout->addWidget(mdiArea, 3);


    tabWidget->addTab(firstTabWidget, tr("Workspace"));

    TopWidget * top = new TopWidget(mm,tabWidget);
    m->addWidget(top);

/*
    QPushButton *newTabButton = new QPushButton("New workspace...");
    newTabButton->setStyleSheet(R"(
 "QPushButton { background-color: white; color: black; border: 1px solid black; }"
    "QPushButton:hover { background-color: lightgray; }"
    "QPushButton:pressed { background-color: gray; }"
    )");
    newTabButton->setCursor(Qt::PointingHandCursor); // Set the cursor to a hand when hovering over the button

    // Connect the button's clicked signal to the slot where you'll add the new tab
    connect(newTabButton, &QPushButton::clicked, this, [this]() {
        int newTabIndex = tabWidget->addTab(new QWidget(), QString("New Tab %1").arg(tabWidget->count() + 1));
        tabWidget->setCurrentIndex(newTabIndex);
    });

    tabWidget->setCornerWidget(newTabButton, Qt::TopRightCorner);
*/



    m->addWidget(tabWidget);
    // Set the central widget
    setCentralWidget(mm);
    std::cout << "MAINWINDOW done"<<std::endl;

}



MainWindow::~MainWindow()
{
}





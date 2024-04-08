#include "midpanel.h"

//MidPanel::MidPanel() {}
#include <QPushButton>
#include <QStyle>

#include "QtWidgets/qmdisubwindow.h"

#include <QTableWidgetItem>
#include <QDateTime>
#include <QRandomGenerator>
#include <iostream>
MidPanel::MidPanel(QWidget *parent,QMdiArea * mdiArea) : QWidget(parent)

{
    std::cout << "MID PANEL"<<std::endl;

    this->mdiArea=mdiArea;

    layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0); // Remove padding around the layout
    layout->setSpacing(0); // Remove spacing between buttons

    // Optional: Set the panel's style to ensure no additional padding or margins
    setStyleSheet("MidPanel { padding: 0px; margin: 0px;   background-color:green; }");
    std::cout << "MID PANEL DONE"<<std::endl;

    this->hide();

}

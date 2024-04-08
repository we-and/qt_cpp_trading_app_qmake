#include "tradewidget.h"

TradeWidget::TradeWidget(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this); // Create the layout and set it to this widget
    labelAvailable = new QLabel("Available to trade", this); // Create the first label
    labelAmount = new QLabel("1000", this); // Create the second label

    // Customize the labels if needed
    labelAvailable->setAlignment(Qt::AlignCenter);
    labelAmount->setAlignment(Qt::AlignCenter);

    // Add the labels to the layout
    layout->addWidget(labelAvailable);
    layout->addStretch(); // This will push the labels to the top and bottom respectively
    layout->addWidget(labelAmount);
}

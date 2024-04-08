#include "searchbutton.h"
#include "QtCore/qdir.h"
#include <QPixmap>
#include <QMouseEvent>
#include <iostream>
SearchButtonWidget::SearchButtonWidget(QWidget *parent) : QWidget(parent) {
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0); // Adjust margins as needed
    layout->setSpacing(0); // Adjust spacing as needed

    QStringList resourcePaths = {":/icons/search.png",};
    foreach (const QString &path, resourcePaths) {
        qDebug() << path;
    }

    // Setup icon label
    iconLabel = new QLabel(this);
    iconLabel->setFixedWidth(50);
    QPixmap pixmap(":/icons/search.png"); // Make sure the path is correct
    iconLabel->setPixmap(pixmap.scaled(20, 20, Qt::KeepAspectRatio)); // Scale the icon as needed
    layout->addWidget(iconLabel,1);

    // Setup text label
    textLabel = new QLabel("Search", this);
    layout->addWidget(textLabel,5);

    textLabel->setStyleSheet(R"(
  QLabel {
            text-align: left;
            border: none;
            background-color: white;font-weight:bold;
            padding: 10px; /* Adjust padding as needed */
            margin: 0px; /* Ensure no margin */
        }
        QLabel:hover {
            background-color: rgba(255, 255, 255, 127); /* 50% opacity for white background */
        }
    )");

    setLayout(layout);

    setAttribute(Qt::WA_Hover, true); // Enable hover events
    updateStyle(false);

//    setCursor(Qt::PointingHandCursor); // Change cursor to indicate clickable
}

void SearchButtonWidget::mousePressEvent(QMouseEvent *event) {
    QWidget::mousePressEvent(event);
    emit clicked(); // Emit the clicked signal
}

void SearchButtonWidget::enterEvent(QEnterEvent *event) {
   QWidget::enterEvent(event); // Always call the base class implementation
    updateStyle(true); // Custom method to update the widget's style for the hovered state
}

void SearchButtonWidget::leaveEvent(QEvent *event) {
    QWidget::leaveEvent(event);
    updateStyle(false); // Update style for non-hover state
}

void SearchButtonWidget::updateStyle(bool hovered) {
    if (hovered) {
        // Light gray background for hovered state
        setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");
    } else {
        // White background for non-hovered state
        setStyleSheet("background-color: white;");
    }
}

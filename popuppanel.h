// PopupPanel.h
#ifndef POPUPPANEL_H
#define POPUPPANEL_H

#include "QtWidgets/qboxlayout.h"
#include <QWidget>
#include <QLabel>

class PopupPanel : public QWidget {
    Q_OBJECT
public:
    explicit PopupPanel(QWidget *parent = nullptr) : QWidget(parent, Qt::ToolTip) {
        setLayout(new QVBoxLayout(this));
        layout()->addWidget(new QLabel("Popup Content Here"));
        // Add more widgets to your popup as needed
    }
};

#endif // P

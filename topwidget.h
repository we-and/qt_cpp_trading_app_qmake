#ifndef TOPWIDGET_H
#define TOPWIDGET_H

#include "customtabwidget.h"
#include "popuppanel.h"
#include <QWidget>
#include <QPushButton>
#include <QComboBox>

#include <QLabel>
#include <QHBoxLayout>

class TopWidget : public QWidget {
    Q_OBJECT

public:
    explicit TopWidget(QWidget *parent = nullptr,CustomTabWidget * tabWidget=nullptr);

private:
    QHBoxLayout * left ;
    CustomTabWidget * tabWidget;
    QHBoxLayout *mainLayout;
    QPushButton *button1; // Example button, you can add more as needed
    QComboBox *comboBox;
    QPushButton *menuButton; // Trigger for the popup
    PopupPanel *popupPanel;
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // TOPWIDGET_H

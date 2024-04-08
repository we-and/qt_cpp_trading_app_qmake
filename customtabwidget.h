#ifndef CUSTOMTABWIDGET_H
#define CUSTOMTABWIDGET_H

#include <QTabWidget>
#include "customtabbar.h"
class CustomTabWidget : public QTabWidget {
    Q_OBJECT
public:
    CustomTabWidget(QWidget *parent = nullptr) : QTabWidget(parent) {
        setTabBar(new CustomTabBar());
        connect(static_cast<CustomTabBar*>(tabBar()), &CustomTabBar::newTabRequested, this, &CustomTabWidget::addNewTab);
    }

private slots:
    void addNewTab() {
        int newTabIndex = addTab(new QWidget(), tr("New Tab"));
        setCurrentIndex(newTabIndex);
    }
};
#endif // CUSTOMTABWIDGET_H

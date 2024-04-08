#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "customtabwidget.h"
#include <QMainWindow>
#include <QMdiArea>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QWidget *midPanel;

public slots:
///        void onTickerTableCellClicked(int row, int column);

    private:
    CustomTabWidget   *tabWidget;
        QWidget *leftPanel;

    QVBoxLayout *leftLayout;
    QMdiArea *mdiArea;
};

#endif // MAINWINDOW_H

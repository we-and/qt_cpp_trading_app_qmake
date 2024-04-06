#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    public slots:
   void onButtonClicked();
        void onCellClicked(int row, int column);
private:
    QWidget *centralWidget;
    QWidget *leftPanel;
    QVBoxLayout *leftLayout;
    QMdiArea *mdiArea;
};

#endif // MAINWINDOW_H

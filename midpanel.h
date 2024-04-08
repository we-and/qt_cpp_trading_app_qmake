#ifndef MIDPANEL_H
#define MIDPANEL_H


#include "mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>


class MidPanel : public QWidget
{
    Q_OBJECT

public:
    explicit MidPanel(QWidget *parent = nullptr, QMdiArea * mdiArea=nullptr);

signals:
//    void tickerTableCellClicked(int row, int column);
  //  void tickerCategoryButtonClicked(int row, int column);
public slots:
    //void onTickerCategoryButtonClicked();
private:
   // QWidget *midPanel;

    QVBoxLayout *layout;
    MainWindow * mainWindow;
    QMdiArea * mdiArea;
};


#endif // MIDPANEL_H

#ifndef TRADEWIDGET_H
#define TRADEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class TradeWidget : public QWidget {
    Q_OBJECT

public:
    explicit TradeWidget(QWidget *parent = nullptr);

private:
    QVBoxLayout *layout;
    QLabel *labelAvailable;
    QLabel *labelAmount;
};

#endif // TRADEWIDGET_H

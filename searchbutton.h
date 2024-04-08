#ifndef SEARCHBUTTONWIDGET_H
#define SEARCHBUTTONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

class SearchButtonWidget : public QWidget {
    Q_OBJECT
public:
    explicit SearchButtonWidget(QWidget *parent = nullptr);


protected:
    void mousePressEvent(QMouseEvent *event) override;
protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
signals:
    void clicked();

private:
    void updateStyle(bool hovered);
    QLabel *iconLabel;
    QLabel *textLabel;
};

#endif // SEARCHBUTTONWIDGET_H

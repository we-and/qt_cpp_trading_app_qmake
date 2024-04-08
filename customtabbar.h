#include <QTabBar>
#include <QPushButton>

class CustomTabBar : public QTabBar {
    Q_OBJECT
public:
    CustomTabBar(QWidget *parent = nullptr) : QTabBar(parent) {
        QPushButton *newTabButton = new QPushButton("+");
        newTabButton->setCursor(Qt::PointingHandCursor);
        this->setStyleSheet("QTabBar::tab { background-color: black; color: white; }"
                                 "QTabBar { background-color: black; }");
        connect(newTabButton, &QPushButton::clicked, this, &CustomTabBar::onNewTabButtonClicked);
        //setCornerWidget(newTabButton, Qt::TopRightCorner);
    }

signals:
    void newTabRequested();

private slots:
    void onNewTabButtonClicked() {
        emit newTabRequested();
    }
};

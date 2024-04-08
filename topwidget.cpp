#include "topwidget.h"
#include "QtCore/qcoreevent.h"
#include "tradewidget.h"

TopWidget::TopWidget(QWidget *parent,CustomTabWidget * tabWidget) : QWidget(parent) {
    // Set the fixed height for the widget
    setFixedHeight(50);
    this->tabWidget=tabWidget;
    setStyleSheet("TopWidget { background-color: #333; }" // Dark grey background for the custom widget
                  "QPushButton { background-color: white;color:white; }" // Slightly lighter grey for buttons
                  "QComboBox { background-color: white; }");


    // Initialize the layout
    mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(0); // Adjust spacing as needed
    mainLayout->setContentsMargins(0, 0,0, 0); // Adjust margins as needed


    QWidget * leftw=new QWidget(this);
    leftw-> setStyleSheet("background-color: #333;");
    left = new QHBoxLayout(leftw);
    mainLayout->addWidget(leftw);
    this->left->setSpacing(0);



     int tabCount = tabWidget->count(); // Get the number of tabs.

     for (int i = 0; i < tabCount; ++i) {
         QString tabText = tabWidget->tabText(i);

         // Create and add buttons to the left side
         button1 = new QPushButton(tabText, this);
         button1->setCursor(Qt::PointingHandCursor);

         button1->setStyleSheet(
             "QPushButton {"
             "    background-color: #333;"
             "    padding:10px;"
             "    color: white;" // Set text color to white for better readability
             "}"
             "QPushButton:hover {"
             "    background-color: #555;"
             "}"
             );
          connect(button1, &QPushButton::clicked, this, [this,i]() {
             this->tabWidget->setCurrentIndex(i);

         });

         // Add more buttons as needed
         left->addWidget(button1);

     }


   QPushButton *  button2 = new QPushButton("+", this);
     button2->setCursor(Qt::PointingHandCursor);
     button2->setStyleSheet(
         "QPushButton {"
         "    background-color: #333;"
         "    padding:10px;"
         "    color: white;" // Set text color to white for better readability
         "}"
         "QPushButton:hover {"
         "    background-color: #555;"
         "}"
         );
     // Connect the button's clicked signal to the slot where you'll add the new tab
     connect(button2, &QPushButton::clicked, this, [this]() {

       int N=this->tabWidget->count();
       QString tabText = QString("Workspace %1").arg(N + 1);

       int newTabIndex = this->tabWidget->addTab(new QWidget(), tabText);
         this->tabWidget->setCurrentIndex(newTabIndex);

       // Create and add buttons to the left side
       button1 = new QPushButton(tabText, this);
         button1->setCursor(Qt::PointingHandCursor);

         button1->setStyleSheet(
             "QPushButton {"
             "    background-color: #333;"
             "    padding:10px;"
             "    color: white;" // Set text color to white for better readability
             "}"
             "QPushButton:hover {"
             "    background-color: #555;"
             "}"
             );
         connect(button1, &QPushButton::clicked, this, [this,N]() {
//           this->tabWidget->setCurrentWidget(myTab);
  this->tabWidget->setCurrentIndex(N);
       });

         // Add more buttons as needed
       this->left->insertWidget(N,button1);

   });


    // Add more buttons as needed
    left->addWidget(button2);



    left->addStretch(); // This pushes everything else to the left



 TradeWidget *tradeWidget = new TradeWidget();
    left->addWidget(tradeWidget);

    // Setup the trigger button
    QPushButton * menuButton0 = new QPushButton("Add funds", this);
    left->addWidget(menuButton0);
    // Setup the trigger button
    QPushButton * menuButton = new QPushButton("Help", this);
    left->addWidget(menuButton);

    QPushButton *    menuButton2 = new QPushButton("Account", this);
    left->addWidget(menuButton2);

    // Initialize the popup panel but do not show it yet
    popupPanel = new PopupPanel(this);
    popupPanel->hide(); // Start hidden

    // Ensure TopWidget accepts hover events
    setAttribute(Qt::WA_Hover, true);
    menuButton2->setAttribute(Qt::WA_Hover, true);
    menuButton2->installEventFilter(this); // Set TopWidget to filter events for menuButton
    setAttribute(Qt::WA_Hover);

    // Add more items to the comboBox as needed
    mainLayout->addWidget(comboBox);

    // Set the layout to the widget
    setLayout(mainLayout);
}

bool TopWidget::eventFilter(QObject *watched, QEvent *event) {
    if (watched == menuButton) {
        if (event->type() == QEvent::Enter) {
            // Show the popup
            QPoint pos = menuButton->mapToGlobal(QPoint(0,menuButton->height()));
            popupPanel->move(pos);
            popupPanel->show();
            return true; // Indicate that the event was handled
        } else if (event->type() == QEvent::Leave) {
            // Hide the popup
            popupPanel->hide();
            return true; // Indicate that the event was handled
        }
    }
    return QWidget::eventFilter(watched, event); // Pass unhandled events to base class
}

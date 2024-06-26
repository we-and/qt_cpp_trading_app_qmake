#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
 std::cout << "START"<<std::endl;
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "qt_cpp_trading_app_qmake_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
//w.show();
    w.showMaximized(); // Show the main window maximized

    return a.exec();
}



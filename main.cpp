#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.show();
//    return a.exec();


    w.testPower();
    w.testBattery();
    w.testSessionSelection();
    w.testConnection();
    w.testIntensitySelection();
    w.testRecordSession();
    w.testReplaySession();
    w.testSelectUser();
        return 0;
}

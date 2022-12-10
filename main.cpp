#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


//  COMMENT THE FOLLOWING 2 LINES TO RUN TESTS
    w.show();
    return a.exec();

////  UNCOMMENT BELOW FOR TESTS
//    w.testPower();
//    w.testBattery();
//    w.testSessionSelection();
//    w.testConnection();
//    w.testIntensitySelection();
//    w.testRecordSession();
//    w.testReplaySession();
//    w.testSelectUser();
//        return 0;
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "session.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


    Session* currentSession; // current in progress session
    bool isConnected;    // true or false, if the wires are connected or not
    int currentTimerCount;  // countdown timer for how long the sesssion has left


    void initializeTimer(QTimer*);  //initialize 1second timer loop
    void startSession(Session*);    //

private slots:
    void updateTimer(); //called everyone 1 second

};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTextList>
#include <QMainWindow>
#include <string>
#include<QDebug>

#include <QtConcurrent>
#include <QThreadPool>
#include <QRandomGenerator>
#include "session.h"
#include "user.h"

/*
Class Purpose - This is the main window of the application and connects functions and functionality to the user interface

Data Members:

User* currentUser - The currently selected user, is "default" by default
Session* currentSession - the current selected session that is undergoing
bool isConnected - a boolean variable that is true if the system is currently connected to the user, and false if not
int currentTimerCount - an int that measures the remaining time of a session in seconds
bool recording - a boolean variable, true if the current session is begin recorded, false if the current session is not

Class Functions:

void initializeTimer(QTimer*) - Initializes the QTimer object to create a loop that calls updateTimer every second as long as device is connected
void startSession(Session*) - Starts the given session 
void updateTimer() - decrements the remaining time of the session by 1 and checks/updates dynamic session and user features.
int recordSession() - records the current session to the current user stored in their respective values
void stopSession() - stops the undergoing session when called
*/




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
    bool Left_Contact;
    bool Right_Contact;
    int Mode_Int;
    bool Power_On;
    double Battery;
    double Draw;
    int Intensity;
    int Intensity2;
    bool Med_Battery;
    bool Low_Battery;
    
    User* currentUser;      //currently selected user.
    Session* currentSession; //the current undergoing session
    bool isConnected;   
    int currentTimerCount; // int that represents time in seconds
    bool recording;

    void initializeTimer(QTimer*);
    void startSession(Session*);

    void initMenu();

    void connectionTest();
    void recordSession();
    void stopSession();

private slots:
    void updateTimer();
    void Traverse();
    void Select();
    void Contact();
    void Update();
    void Power();
    void SetPowerAdmin();
    void SetPower(int);
    void SetIntensityAdmin();
    void SetIntensity(int);
    void SetIntensity2Admin();
    void SetIntensity2(int);
    void ModeSwap();
    void UseAdmin();
    void SetDraw(double);
};
#endif // MAINWINDOW_H

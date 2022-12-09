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
#include "menu.h"

/*
Class Purpose - This is the main window of the application and connects functions and functionality to the user interface

Data Members:

User* currentUser - The currently selected user, is "default" by default
Session* currentSession - the current selected session that is undergoing
bool isConnected - a boolean variable that is true if the system is currently connected to the user, and false if not
int currentTimerCount - an int that measures the remaining time of a session in seconds
Menu* currentMenu - the current menu the user is in
Menu* forDestructorMenu - to delete the current menu pointer


Class Functions:

void initializeTimer(QTimer*) - Initializes the QTimer object to create a loop that calls updateTimer every second as long as device is connected
void startSession(Session*) - Starts the given session 
void updateTimer() - decrements the remaining time of the session by 1 and checks/updates dynamic session and user features.
int recordSession() - records the current session to the current user stored in their respective values
void stopSession() - stops the undergoing session when called
void initMenu(Menu*) - Creates, initializes and displays sub menus
void menuUpdate(Menu*) - updates menu display
void displaySession() - displays the timer when in a session
void updateDisplaySession() - void updates the timer display when in a session;
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

    // Testing functions
    void testPower();
    void testBattery();
    void testSessionSelection();
    void testConnection();
    void testIntensitySelection();
    void testRecordSession();
    void testReplaySession();
    void testSelectUser();


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
    int duration;
    bool recording;
    
    User* currentUser;      //currently selected user.
    Session* currentSession; //the current undergoing session
    bool isConnected;   
    int currentTimerCount; // int that represents time in seconds
    Menu* currentMenu;
    Menu* forDestructorMenu;
    QVector<Session*> sessionList;
    QVector<User*> userList;//?

    void initializeTimer(QTimer*);
    void startSession(Session*);

    void initMenu(Menu*);
    
    void stopSession();
    void menuUpdate(Menu*);
    void displaySession();
    void updateDisplaySession();
    void updateSessionList();

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
    void connectionTest(bool); //Yacin start //Yacin end
    void connectionTest(int); //Yacin start //Yacin end
    void goBack();
    void recordSession();
};
#endif // MAINWINDOW_H

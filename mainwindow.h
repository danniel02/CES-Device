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
    
    Session* currentSession;
    bool isConnected;
    int currentTimerCount;

    void initializeTimer(QTimer*);
    void startSession(Session*);

    void initMenu();

    void connectionTest();

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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTextList>
#include <QMainWindow>
#include <string>
#include<QDebug>

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
    int Intensity;
    int Intensity2;
    bool Med_Battery;
    bool Low_Battery;
private slots:
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
};
#endif // MAINWINDOW_H

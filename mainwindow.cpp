#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->UP, SIGNAL(pressed()),this,SLOT(Traverse()));
    connect(ui->DOWN, SIGNAL(pressed()),this,SLOT(Traverse()));
    connect(ui->L_CON_B, SIGNAL(pressed()),this,SLOT(Contact()));
    connect(ui->R_CON_B, SIGNAL(pressed()),this,SLOT(Contact()));
    connect(ui->POWER_B, SIGNAL(pressed()),this,SLOT(Power()));
    connect(ui->SET_BAT, SIGNAL(pressed()),this,SLOT(SetPowerAdmin()));
    connect(ui->SET_INT, SIGNAL(pressed()),this,SLOT(SetIntensityAdmin()));
    connect(ui->SET_INT2, SIGNAL(pressed()),this,SLOT(SetIntensity2Admin()));
    connect(ui->MODE, SIGNAL(pressed()),this,SLOT(ModeSwap()));
    connect(ui->USE_ADMIN, SIGNAL(pressed()),this,SLOT(UseAdmin()));


    Left_Contact=false;
    Right_Contact=false;
    Mode_Int=0;
    Power_On=false;
    Battery=100;
    Intensity=0;
    Low_Battery=false;
    Med_Battery=false;


    Update();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Traverse(){
    QPushButton* up_down = qobject_cast<QPushButton*>(sender());
    qInfo()<<"selected: "<<up_down->text();
    //do with this what you will
}

void MainWindow::Select(){
    //do with this what you will
}

void MainWindow::Contact(){
    QPushButton* L_R = qobject_cast<QPushButton*>(sender());
    qInfo()<<"Connect/Disconnect: "<<L_R->text();
    if (L_R->text()=="L_CON"){
        Left_Contact= !Left_Contact;
        qInfo()<<"Left Con now: "<<Left_Contact;

    }else{
        Right_Contact= !Right_Contact;
        qInfo()<<"Right Con now: "<<Right_Contact;
    }
    Update();
    //do with this what you will
}

void MainWindow::Update(){
    qInfo()<<"updating";
    //updates menu and all lights;
    //L/R contact, Mode, Power, power warning, menu, intensity
    if (Left_Contact){
        //set it to green
        ui->L_CON->setStyleSheet("background-color: green");

    }else{
        //set to red
        ui->L_CON->setStyleSheet("background-color: red");
    }

    if (Right_Contact){
        //set it to green
        ui->R_CON->setStyleSheet("background-color: green");
    }else{
        //set to red
        ui->R_CON->setStyleSheet("background-color: red");
    }
    //qInfo()<<"style:"<<ui->L_CON->styleSheet();
    //ui->R_CON->update();

    if (Power_On){
        //everything is allowed to be on
        ui->POWER_B->setStyleSheet("background-color: green");

    }else{
        //turn all lights to white, reset
        ui->POWER_B->setStyleSheet("background-color: white");
    }

    //battery and warnning
    ui->BAT->setValue(Battery);
    if (Med_Battery){
        //set to orange
        ui->LOW->setStyleSheet("background-color: orange");
    }
    if(Low_Battery){
        ui->LOW->setStyleSheet("background-color: red");

    }
    if (Battery==0){
        //set all to off, TODO: have it deactivate all buttons asswell and clear settings,
        //bassically startup again, maybe need to shift startup to its own function for restart
        qInfo()<<"no Power, shut down";
    }

    //intensity
    ui->INT->setValue(Intensity);
    ui->INT_2->setValue(Intensity2);



    //mode
    switch (Mode_Int) {
    case 0:
        ui->M1->setStyleSheet("background-color: green");
        ui->M2->setStyleSheet("background-color: red");
        ui->M3->setStyleSheet("background-color: red");
        break;
    case 1:
        ui->M1->setStyleSheet("background-color: red");
        ui->M2->setStyleSheet("background-color: green");
        ui->M3->setStyleSheet("background-color: red");

        break;
    case 2:
        ui->M1->setStyleSheet("background-color: red");
        ui->M2->setStyleSheet("background-color: red");
        ui->M3->setStyleSheet("background-color: green");
        break;
    }



}
void MainWindow::Power(){

    Power_On = !Power_On;
    qInfo()<<"power is:"<<Power_On;
    Update();//should turn everything off

}

void MainWindow::SetPowerAdmin(){
    //do
    double P_Bar = ui->SPIN_BAT->value();
    qInfo()<<"slider setting power to:"<<P_Bar;
    Battery = P_Bar;
    if (P_Bar<15){
        Med_Battery=true;
    }
    if (P_Bar<5){
        Low_Battery=true;
    }
    Update();

}
void MainWindow::SetPower(int i){
    //do
    qInfo()<<"slider setting power to:"<<i;
    Battery = i;
    if (i<15){
        Med_Battery=true;
    }else{
        Med_Battery=false;
    }
    if (i<5){
        Low_Battery=true;
    }else{
        Low_Battery=false;
    }
    Update();

}

void MainWindow::SetIntensity(int i){
    //do
    qInfo()<<"intensity to:"<<i;
    Intensity = i;

    Update();

}
void MainWindow::SetIntensity2(int i){
    //do
    qInfo()<<"intensity to:"<<i;
    Intensity2 = i;
    Update();

}
void MainWindow::SetIntensityAdmin(){
    //do
    double i = ui->SPIN_INT->value();
    qInfo()<<"intensity to:"<<i;


    Intensity = i;

    Update();

}
void MainWindow::SetIntensity2Admin(){
    //do
    double i = ui->SPIN_INT2->value();
    qInfo()<<"intensity to:"<<i;


    Intensity2 = i;
    Update();

}
void MainWindow::ModeSwap(){
    //just add 1 to mode, if its now 3, set it to 0
    Mode_Int++;
    if (Mode_Int==3){
        Mode_Int=0;
    }
    Update();

}
void MainWindow::UseAdmin(){

    double i = ui->SPIN_USE_ADMIN->value();
    qInfo()<<"Use:"<<i;
    if (Battery-i>0){
        SetPower(Battery-i);
    }else{
        Battery = 0;
    }
    Update();

}

void MainWindow::initializeTimer(QTimer* t){
    connect(t, &QTimer::timeout, this, &MainWindow::updateTimer);

    if (isConnected) {
        t->start(1000);
    }
}

void MainWindow::updateTimer(){
    currentTimerCount -= 1;
    if (currentTimerCount == 0){
        currentTimerCount = -1
        currentSession->getTimer()->stop();
        currentSession->getTimer()->disconnect();
        currentSession = nullptr;
    }
}

void MainWindow::startSession(Session *s){
    currentSession = s;

    currentTimerCount = s->getTime();
    initializeTimer(s->getDuration);

}




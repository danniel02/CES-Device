#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Yacin start
    //Creating and initializing the main menu
    currentMenu = new Menu("START",{"Start Session", "Review Session", "Login/out"},nullptr);
    forDestructorMenu = currentMenu;

    //Creates, initializes and displays sub menus
    initMenu(currentMenu);
    //Yacin end

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
    //Yacin start
    connect(ui->ENTER, SIGNAL(pressed()),this,SLOT(Select()));
    connect(ui->RETURN, SIGNAL(pressed()),this,SLOT(goBack()));
    ui->CT_LIST->addItems({"No Connection", "Okay Connection", "Excellent Connection"}); // Connection test QComboBox initialization & connections
    connect(ui->CT_LIST, QOverload<int>::of(&QComboBox::activated), this, QOverload<int>::of(&MainWindow::connectionTest));
    //Yacin end

    Left_Contact=false;
    Right_Contact=false;
    Mode_Int=0;
    Power_On=false;
    Battery=100;
    Intensity=0;
    Low_Battery=false;
    Med_Battery=false;

    currentUser = new User("Default"); // set the current user as a default
    currentSession = nullptr;

    Update();







}

MainWindow::~MainWindow()
{
    delete ui;
    delete forDestructorMenu;
}

void MainWindow::Traverse(){
    QPushButton* up_down = qobject_cast<QPushButton*>(sender());
    qInfo()<<"selected: "<<up_down->text();
    //do with this what you will
    //Yacin start

    //traverse up the menu's options
    if(up_down->text()=="UP"){
        //loops down to bottom if at upper limit
        if( (ui->menuViewer->currentRow()-1) < 0 ){
            ui->menuViewer->setCurrentRow(ui->menuViewer->count()-1);
        }
        else{
            ui->menuViewer->setCurrentRow(ui->menuViewer->currentRow()-1);
        }
    }

    //traverse down the menu's options
    else if(up_down->text()=="DOWN"){
        //loops up to top if at lower limit
        if( (ui->menuViewer->count()-1) < (ui->menuViewer->currentRow()+1) ){
            ui->menuViewer->setCurrentRow(0);

        }
        else{
            ui->menuViewer->setCurrentRow(ui->menuViewer->currentRow()+1);
        }
    }

    //Yacin end
}

void MainWindow::Select(){
    //do with this what you will
    //Yacin start
    QPushButton* selected = qobject_cast<QPushButton*>(sender());
     qInfo()<<"selected: "<<selected->text();

    //if selection is session call creation of session
    //else traverse multi dimension array

    int indexMenu = ui->menuViewer->currentRow();
    //if(currentMenu->get(indexMenu)->hasChildMenu()){

    if(currentMenu->hasChildMenu()){
        qInfo()<<"test2";
        currentMenu = currentMenu->get(indexMenu);
        menuUpdate(currentMenu);
    }else{
        qInfo()<<"test";

        QString name=ui->MENU_LABEL->text();

        QString* n = currentMenu->getName(indexMenu);
        //qInfo()<<*n;
        if (name == "UserSelect"){
            qInfo()<<name;
            qInfo()<<*n;
        }else if(name == "Session Creation"){
            qInfo()<<name;
            qInfo()<<*n;
        }else if(name == "Session List"){
            qInfo()<<name;
            qInfo()<<*n;
        }
    }
    //ADD LOGIC HERE
    //options, start/create session, select user, view session

    //Yacin end
}

//Yacin start
void MainWindow::goBack(){
    QPushButton* back = qobject_cast<QPushButton*>(sender());
    qInfo()<<"selected: "<<back->text();
    if(currentMenu->getParent()!=nullptr){
        currentMenu = currentMenu->getParent();
    }
    else{return;}
    menuUpdate(currentMenu);
}
//Yacin end

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

    //Yacin start
    if((Left_Contact==false)||(Right_Contact==false)){
        //PAUSE SESSION
        ui->CT_LIST->setCurrentIndex(0);
        ui->CON_T->setStyleSheet("background-color: red");
        isConnected=false;
    }
    else{
        //CONTINUE SESSION
        ui->CT_LIST->setCurrentIndex(2);
        ui->CON_T->setText("Excellent Connection");
        ui->CON_T->setStyleSheet("background-color: green");
        isConnected=true;
    }
    ui->CON_T->setText(ui->CT_LIST->currentText());
    //Yacin end
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
        ui->OFF_SCREEN->setVisible(false);
        ui->UP->blockSignals(false);
        ui->DOWN->blockSignals(false);
        ui->ENTER->blockSignals(false);
        ui->RETURN->blockSignals(false);

    }else{
        //turn all lights to white, reset
        ui->POWER_B->setStyleSheet("background-color: white");
        ui->OFF_SCREEN->setVisible(true);
        ui->UP->blockSignals(true);
        ui->DOWN->blockSignals(true);
        ui->ENTER->blockSignals(true);
        ui->RETURN->blockSignals(true);
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

    if (Mode_Int==0){
        QtConcurrent::run([this]{
            return;
        });

    }

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
void MainWindow::SetDraw(double i){
    qInfo()<<"Use:"<<i;
    Draw=i;
    if (Battery-Draw>0){
        SetPower(Battery-Draw);
    }else{
        Battery = 0;
    }
}

void MainWindow::initializeTimer(QTimer* t){
    //calls update timer ever 1 second until explicit call is made to stop or disconnect the timer
    connect(t, &QTimer::timeout, this, &MainWindow::updateTimer);
    if (isConnected) {
        t->start(1000);
    }
}

void MainWindow::updateTimer(){
    currentTimerCount -= 1;

    //do i set this to Intensity or Intensity2?
    currentSession->setIntensity(Intensity);


    if (currentTimerCount == 0){
        currentTimerCount = -1;
        currentSession->getTimer()->stop();
        currentSession->getTimer()->disconnect();
        currentSession = nullptr;
    }
}

// call to start a session
void MainWindow::startSession(Session *s){
    if(currentSession != nullptr) { return; }
    currentSession = s;

    currentTimerCount = s->getDuration();
    initializeTimer(s->getTimer());

}

void MainWindow::stopSession(){
    if(currentTimerCount > 0){
        currentTimerCount = -1;
        currentSession->getTimer()->stop();
        currentSession->getTimer()->disconnect();
        currentSession = nullptr;
    }

}

void MainWindow::recordSession(){    //uses currentUser variable to record a currently undergoing session to the current user vector
    if(currentTimerCount < 1){ return; } // if session is not currently undergoing, cannot record. Needs clarification on when you're able to record
    currentUser->addSession(currentSession);
}

//MENU NAV

void MainWindow::initMenu(Menu* currentM){
    //start up we need 5 menus, Start(Start Session, Review Sessions, Login/out), Session Creation(Initial Power Level, Session duration:)..the other 2 are not needed,Session List(all recorded sessions),login/out()
    //maybe make some lists and beased on what is clicked it either transfers to another list or modifies the current one
    //QTreeView ?

    //Yacin start
    //creation of sub menus
    Menu* sessionCreation= new Menu("Session Creation",{"?","??","etc.."},currentM);
    Menu* sessionList= new Menu("Session List",{"1. Session:#?","etc.."},currentM);
    Menu* userSelect= new Menu("UserSelect",{"User ?","User ??","etc.."},currentM);

    //add sub menus to main menu
    currentM->addChildMenu(sessionCreation);
    currentM->addChildMenu(sessionList);
    currentM->addChildMenu(userSelect);

    //add sub menus to the sub menus below
    //do with this what you will


    //display start menu to the ui
    ui->menuViewer->addItems(currentM->getMenuItems());
    ui->menuViewer->setCurrentRow(0);
    ui->MENU_LABEL->setText(currentM->getName());

    //Yacin end
    }

//Yacin start
void MainWindow::connectionTest(bool checked) {

    Left_Contact = checked;
    Right_Contact = checked;
    //IF CHECKED IS FALSE THEN PAUSE CONNECTION
    if(checked==false){
        isConnected=false;
    }
    Update();
}


void MainWindow::connectionTest(int indexVal) {

    ui->CON_T->setText(ui->CT_LIST->currentText());

    if(indexVal==1){
        ui->CON_T->setStyleSheet("background-color: yellow");
    }
    else if(indexVal==2){
        ui->CON_T->setStyleSheet("background-color: green");
    }
    connectionTest((indexVal == 1) || (indexVal == 2)) ;
}

void MainWindow::menuUpdate(Menu* currentM){
    ui->menuViewer->clear();
    ui->menuViewer->addItems(currentM->getMenuItems());
    ui->menuViewer->setCurrentRow(0);
    ui->MENU_LABEL->setText(currentM->getName());
}

//Yacin end
















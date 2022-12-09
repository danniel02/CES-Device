#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    userList.push_back(new User("1Default"));
    currentUser = userList[0]; // set the current user as a default
    initMenu(currentMenu);
    //Yacin end

    connect(ui->UP, SIGNAL(pressed()),this,SLOT(Traverse()));
    connect(ui->DOWN, SIGNAL(pressed()),this,SLOT(Traverse()));
    connect(ui->L_CON_B, SIGNAL(pressed()),this,SLOT(Contact()));
    connect(ui->R_CON_B, SIGNAL(pressed()),this,SLOT(Contact()));
    connect(ui->POWER_B, SIGNAL(pressed()),this,SLOT(Power()));
    connect(ui->SET_BAT, SIGNAL(pressed()),this,SLOT(SetPowerAdmin()));
    connect(ui->SPIN_INT, SIGNAL(valueChanged(int)),this,SLOT(SetIntensityAdmin()));
    connect(ui->SET_INT2, SIGNAL(pressed()),this,SLOT(SetIntensity2Admin()));
    connect(ui->MODE, SIGNAL(pressed()),this,SLOT(ModeSwap()));
    connect(ui->USE_ADMIN, SIGNAL(pressed()),this,SLOT(UseAdmin()));
    connect(ui->RECORD, SIGNAL(pressed()),this,SLOT(recordSession()));
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
    Intensity=ui->SPIN_INT->value();
    Low_Battery=false;
    Med_Battery=false;
    duration=0;
    isConnected=false;
    Draw=0.0;
    recording = false;


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
        if(currentMenu->getName()=="Set User Designated Session Type"){
            ui->USER_DESG_TIME->setValue(ui->USER_DESG_TIME->value()+1);
        }
        else{
            //loops down to bottom if at upper limit
            if( (ui->menuViewer->currentRow()-1) < 0 ){
                ui->menuViewer->setCurrentRow(ui->menuViewer->count()-1);
            }
            else{
                ui->menuViewer->setCurrentRow(ui->menuViewer->currentRow()-1);
            }
        }
    }

    //traverse down the menu's options
    else if(up_down->text()=="DOWN"){
        if(currentMenu->getName()=="Set User Designated Session Type"){
            ui->USER_DESG_TIME->setValue(ui->USER_DESG_TIME->value()-1);
        }
        else{
            //loops up to top if at lower limit
            if( (ui->menuViewer->count()-1) < (ui->menuViewer->currentRow()+1) ){
                ui->menuViewer->setCurrentRow(0);

            }
            else{
                ui->menuViewer->setCurrentRow(ui->menuViewer->currentRow()+1);
            }
        }

    }

    //Yacin end
}

void MainWindow::Select(){
    //do with this what you will
    //Yacin start


    QPushButton* selected = qobject_cast<QPushButton*>(sender());
     qInfo()<<"selected: "<<selected->text();

    //For tracking
    int indexMenu = ui->menuViewer->currentRow();
    QStringList groups = {"Session Type for 20 Minutes","Session Type for 45 Minutes","User Designated Session Type"};
    QStringList frequencyList = {"6-8 Hz","9-11 Hz","12-15 Hz","18-22 Hz"};
    QString name= ui->MENU_LABEL->text();

    //if selection is session call creation of session
    //else traverse multi dimension array
    if(name == "START"){ updateSessionList();}
    if(currentMenu->hasChildMenu()){
        currentMenu = currentMenu->get(indexMenu);
        //qInfo()<<"THE NAME:"<<currentMenu->getName();
        //Yacin change
        if(currentMenu->getName() == groups[0]){
            duration = 20;
            qInfo()<<"selected option:"<<currentMenu->getName();
        }
        else if(currentMenu->getName() == groups[1]){
            duration = 45;
            qInfo()<<"selected option:"<<currentMenu->getName();
        }
        else if(currentMenu->getName() == groups[2]){
            duration= ui->USER_DESG_TIME->value();
            ui->USER_DESG_TIME->setValue(0);
            qInfo()<<"selected option:"<<currentMenu->getName();
        }
        menuUpdate(currentMenu);
    }
    else{
        if(name == "UserSelect"){
            qInfo()<<"switching user from"<<currentUser->getName();
            //does not work, need to init the right var names
            qInfo()<<ui->menuViewer->currentRow();
            //for (int i=0;i<userList.length();i++){

            //    if (selected->text() == userList[i]->getName()){
            //        currentUser==userList[i];
            //    }
            //}
            currentUser= userList[ui->menuViewer->currentRow()];
            qInfo()<<"to:"<<currentUser->getName();
            currentMenu = currentMenu->getParent();
            menuUpdate(currentMenu);//might wanna shift these down to the bottom
        }
        else if(name == "Session Creation"){          
            qInfo()<<"Something fun";
        }
        else if(name == "Session List"){
            qInfo()<<name;
            Session* selectedSess = currentUser->getSessions()[indexMenu];
            startSession(selectedSess);
            displaySession();
        }
        else if(name == groups[0]||name == groups[1]||name == groups[2]){
            //variables to create session
            QString frequencyName = currentMenu->getMenuItems()[indexMenu];
            QString frequencyWaveLength = frequencyList[indexMenu];

            qInfo()<<"selected session frequency:"<<frequencyName;

            qInfo()<<"starting session...";
            currentSession = nullptr;
            Session* tempSession = new Session(frequencyName,frequencyWaveLength,duration,Intensity);
            startSession(tempSession);
            displaySession();
        }

    }
    //qInfo()<<ui->MENU_LABEL->text();
    //ADD LOGIC HERE
    //Yacin end
}

//Yacin start
void MainWindow::goBack(){
    QPushButton* back = qobject_cast<QPushButton*>(sender());
    qInfo()<<"selected: "<<back->text();
    if(currentSession!=nullptr){
        stopSession();
    }
    else if(currentMenu->getParent()!=nullptr){
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
    if (Battery<=0){
        //set all to off, TODO: have it deactivate all buttons asswell and clear settings,
        //bassically startup again, maybe need to shift startup to its own function for restart
        Power();

        qInfo()<<"no Power, shut down";
    }

    //intensity
    //Intensity=ui->SPIN_INT->value();
    ui->INT->setValue(Intensity);
    ui->INT_2->setValue(Intensity2);



    //mode
    switch (Mode_Int) {
    case 0:
        ui->M1->setStyleSheet("background-color: green");
        ui->M2->setStyleSheet("background-color: red");
        ui->M3->setStyleSheet("background-color: red");
        ui->M4->setStyleSheet("background-color: red");
        break;
    case 1:
        ui->M1->setStyleSheet("background-color: red");
        ui->M2->setStyleSheet("background-color: green");
        ui->M3->setStyleSheet("background-color: red");
        ui->M4->setStyleSheet("background-color: red");
        break;
    case 2:
        ui->M1->setStyleSheet("background-color: red");
        ui->M2->setStyleSheet("background-color: red");
        ui->M3->setStyleSheet("background-color: green");
        ui->M4->setStyleSheet("background-color: red");
        break;
    case 3:
        ui->M1->setStyleSheet("background-color: red");
        ui->M2->setStyleSheet("background-color: red");
        ui->M3->setStyleSheet("background-color: red");
        ui->M4->setStyleSheet("background-color: green");
        break;

    }


}
void MainWindow::Power(){

    Power_On = !Power_On;
    qInfo()<<"power is:"<<Power_On;
    stopSession();
    currentMenu=forDestructorMenu;
    menuUpdate(currentMenu);
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
    if (Mode_Int==4){
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
    Draw=i/2;
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
        updateDisplaySession();
        t->start(1000);
    }
}

void MainWindow::updateTimer(){

    currentTimerCount -= 1;

    //do i set this to Intensity or Intensity2?
    currentSession->setIntensity(Intensity);

    updateDisplaySession();
    SetDraw(Intensity);

    if (currentTimerCount <= 0){
        if(recording){ 
            currentUser->addSession(currentSession); 
            updateSessionList();
        }
        currentTimerCount = -1;
        currentSession->getTimer()->stop();
        currentSession->getTimer()->disconnect();
        currentSession = nullptr;
        currentMenu = forDestructorMenu;
        recording = false;
        menuUpdate(currentMenu);
    }
}

// call to start a session
void MainWindow::startSession(Session *s){
    if(currentSession != nullptr) { return; }
    currentSession = s;
    qInfo()<< s->getDuration();
    currentTimerCount = s->getDuration();
    initializeTimer(s->getTimer());

}

void MainWindow::stopSession(){
    if(currentTimerCount > 0){
        if(recording){ 
            currentUser->addSession(currentSession); 
            

            updateSessionList();
        }
        currentTimerCount = -1;
        currentSession->getTimer()->stop();
        currentSession->getTimer()->disconnect();
        currentSession = nullptr;
        recording = false;
        updateDisplaySession();
    }

}

void MainWindow::recordSession(){    //uses currentUser variable to record a currently undergoing session to the current user vector
    qInfo()<<"test";
    if(currentTimerCount < 1){ return; } // if session is not currently undergoing, cannot record. Needs clarification on when you're able to record
    recording = true;
    
}

//MENU NAV

void MainWindow::initMenu(Menu* currentM){
    //start up we need 5 menus, Start(Start Session, Review Sessions, Login/out), Session Creation(Initial Power Level, Session duration:)..the other 2 are not needed,Session List(all recorded sessions),login/out()
    //maybe make some lists and beased on what is clicked it either transfers to another list or modifies the current one
    //QTreeView ?

    //Yacin start
    //creation of sub menus
    Menu* sessionCreation= new Menu("Session Creation",{"20 Minutes","45 Minutes","User Designated"},currentM); //Yacin Change
    Menu* sessionList= new Menu("Session List",{},currentM);
    //ben edit, adding dynamic users
    userList.push_back(new User("Ben"));
    userList.push_back(new User("Danniel"));
    userList.push_back(new User("Duc"));
    userList.push_back(new User("Yacin"));
    for (int j=0;j<userList.length();j++){
        qInfo()<<userList[j]->getName();
    }
    Menu* userSelect= new Menu("UserSelect",{"1Default","Ben","Danniel","Duc","Yacin"},currentM);

    //add sub menus to main menu
    currentM->addChildMenu(sessionCreation);
    currentM->addChildMenu(sessionList);
    currentM->addChildMenu(userSelect);

    //add sub menus to the sub menus below
    //do with this what you will

    Menu* min20= new Menu("Session Type for 20 Minutes",{"Theta","Alpha","Beta 1","Beta 2"},sessionCreation); //Yacin Change
    Menu* min45= new Menu("Session Type for 45 Minutes",{"Theta","Alpha","Beta 1","Beta 2"},sessionCreation); //Yacin Change
    Menu* setUserDesg= new Menu("Set User Designated Session Type",{"Null"},sessionCreation); //Yacin Change
    Menu* minUserDesg= new Menu("User Designated Session Type",{"Theta","Alpha","Beta 1","Beta 2"},setUserDesg); //Yacin Change

    sessionCreation->addChildMenu(min20);
    sessionCreation->addChildMenu(min45);
    sessionCreation->addChildMenu(setUserDesg);
    setUserDesg->addChildMenu(minUserDesg);


    //display start menu to the ui
    ui->menuViewer->addItems(currentM->getMenuItems());
    ui->menuViewer->setCurrentRow(0);
    ui->MENU_LABEL->setText(currentM->getName());
    ui->USER_DESG_TIME->setVisible(false);

    //Yacin end
    }

//Yacin start
void MainWindow::connectionTest(bool checked) {

    Left_Contact = checked;
    Right_Contact = checked;
    //IF CHECKED IS FALSE THEN PAUSE CONNECTION
    if(checked==false){
        isConnected=false;
        ui->CON_T->setStyleSheet("background-color: red");
        if(currentSession!=nullptr){
            stopSession();
            menuUpdate(currentMenu);
        }
    }
    else{
        isConnected=true;
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

    if(currentM->getName()=="Set User Designated Session Type"){
        ui->menuViewer->setVisible(false);
        ui->USER_DESG_TIME->setVisible(true);
        ui->TIME_SCREEN->setVisible(false);
    }
    else{
        ui->menuViewer->setVisible(true);
        ui->USER_DESG_TIME->setVisible(false);
        ui->TIME_SCREEN->setVisible(false);
    }
    //if (currentM->getName("Session List")){

     //   currentMenu->get(1)->addMenuItem(n);
    //}
}


void MainWindow::displaySession(){
    ui->menuViewer->setVisible(false);
    ui->USER_DESG_TIME->setVisible(false);
    ui->TIME_SCREEN->setVisible(true);
}

void MainWindow::updateDisplaySession(){
    qInfo()<<"Isrecording?"<<recording;
    qInfo()<<"TIME LEFT:"<<currentTimerCount;
    QString s;
    if(currentTimerCount>60){
        int hours = currentTimerCount / 60;
        int minutes = currentTimerCount-(60*hours);
        s = QStringLiteral("%1").arg(hours, 2, 10, QLatin1Char('0')) + ":" +QStringLiteral("%1").arg(minutes, 2, 10, QLatin1Char('0'));
    }
    s = QStringLiteral("%1").arg(0, 2, 10, QLatin1Char('0')) + ":" +QStringLiteral("%1").arg(currentTimerCount, 2, 10, QLatin1Char('0'));
    ui->TIME_SCREEN->setText(s);
}
//Yacin end


void MainWindow::updateSessionList(){
    while(1){
        if(currentMenu->getName() == "START"){
            break;
        }
        currentMenu = currentMenu->getParent();
    }
    currentMenu->get(1)->clearItems();
    for (int i=0;i<currentUser->getSessions().length();i++){
        QString n = QString("Freq: %1, Dur: %2").arg(currentUser->getSessions()[i]->getName(), QString::number(currentUser->getSessions()[i]->getDuration()));
        currentMenu->get(1)->addMenuItem(n);
    }
}











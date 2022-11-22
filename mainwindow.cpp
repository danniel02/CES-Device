#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initializeTimer(QTimer* t) {

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
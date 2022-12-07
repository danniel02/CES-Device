#include "session.h"

Session::Session(QString n, QString f, int d, int i){
    name = n;
    freq = f;
    duration = d;
    intensity = i;

    timer = new QTimer(this);
}

Session::~Session(){
    delete timer;
}

QString Session::getName() { return name; }
int Session::getDuration() { return duration; }
QString Session::getFreq() { return freq; }
QTimer* Session:: getTimer() { return timer; }
int Session::getIntensity(){ return intensity; }
void Session::setIntensity(int i){ intensity = i; }

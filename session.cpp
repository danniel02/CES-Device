#include "session.h"

Session::Session(QString n, QString f, int d){
    name = n;
    freq = f;
    duration = d;

    timer = new QTimer(this);
}

Session::~Session{
    delete timer;
}

QString Session::getName() { return name; }
int Session::getDuration() { return duration; }
QString Session::getFreq() { return freq; }
QTimer* Session:: getTimer() { return timer; }
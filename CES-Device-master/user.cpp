#include "user.h"

User::User(QString n){
    userName = n;
    
}

User::~User(){
    for(int i = 0; i < sessions.length(); i++){
        delete sessions[i];
    }
}

void User::addSession(Session* s){
    sessions.push_back(s);
}

QString User::getName(){ return userName; }
QVector<Session*> User::getSessions() {return sessions; }

#ifndef USER_H
#define USER_H


#include <QString>
#include <QVector>
#include "session.h"

/*
User Class - Purpose: to organize user data, mainly their recorded and saved sessions and their name

Class Functions: 
- getters and setters

Class Member Variables: 
- QVector<Session*> sessions // A QVector containing a list of completed and recorded sessions for the user
- QString username // the name of the user
*/
class User {
    public:
        User(QString name);
        ~User();
        void addSession(Session* s);
        QString getName();
        QVector<Session*> getSessions();

    private:
        QVector<Session*> sessions;
        QString userName;


};


#endif

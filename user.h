#ifndef USER_H
#define USER_H


#include <QString>
#include <QVector>
#include "session.h"

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

#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QString>
#include <QTimer>

class Session : public QObject{

    Q_Object

    public:
        Session(const QString name, const QString freq, int dur);
        ~Session();

        QString getName();
        QString getFreq();
        QTimer* getTimer();
        int getDuration();


    private:
        int duration;
        QTimer *timer;
        QString name;
        QString freq;


};

#endif
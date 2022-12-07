#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QString>
#include <QTimer>


/*
Session Class - Purpose: to organize session data

Class Functions: 
- getters and setters

Class Member Variables: 
- int duration // an integer representing the length/duration of a session
- QTimer *timer // a QTimer object that keeps track of the length of the session
- QString name // The session type name ie alpha, beta
- QString freq // the session frequency in a string. ie "10-12Hz". This is not used besides for keeping track of wavelength data
- int intensity // the current intensity of the session from 0-8 where 0 is default value and means not active.
*/
class Session : public QObject{

    Q_OBJECT

    public:
        Session(const QString name, const QString freq, int dur, int i);
        ~Session();

        QString getName();
        QString getFreq();
        QTimer* getTimer();
        int getDuration();
        int getIntensity();
        void setIntensity(int i);


    private:
        int duration;
        QTimer *timer;
        QString name;
        QString freq;
        int intensity; //1-8, 0 means off or no power or no connection


};

#endif

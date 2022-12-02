#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QString>
#include <QTimer>

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



#ifndef CSOUNDOBJECT_H
#define CSOUNDOBJECT_H

#include <QObject>
#include <QThread>

#include <csound.hpp>



//#include <csound.h>
class CsoundObject : public QThread
{
	Q_OBJECT
public:
    explicit CsoundObject();
    Csound *getCsound() {return cs;}
    void setCsd(QString csd) {csdFile = csd;}
    void run();
    enum States {Playing, Stopped, Error};

signals:
    void statusChanged(int status);
    //void forwardChannelValue(QString channel, double value);

public slots:
//    void setChannel(QString channel, double value);
//    double getChannel(QString channel);
//    void scoreEvent(QString event);
    //void play();
    void stop();


private:
	Csound  *cs;
	bool stopNow;
    QString csdFile;
};

#endif // CSOUNDOBJECT_H

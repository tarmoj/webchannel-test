

#ifndef CSOUNDOBJECT_H
#define CSOUNDOBJECT_H

#include <QObject>

#include <csound.hpp>



//#include <csound.h>
class CsoundObject : public QObject
{
	Q_OBJECT
public:
	explicit CsoundObject(QObject *parent = 0);
    Csound *getCsound() {return cs;}
    void setCsd(QString csd) {csdFile = csd;}

    enum States {Playing, Stopped, Error};

signals:
    void statusChanged(int status);

public slots:
//    void setChannel(QString channel, double value);
//    double getChannel(QString channel);
//    void scoreEvent(QString event);
    void play();
    void stop();


private:
	Csound  *cs;
	bool stopNow;
    QString csdFile;
};

#endif // CSOUNDOBJECT_H

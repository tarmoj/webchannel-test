#ifndef CSOUNDWRAPPER_H
#define CSOUNDWRAPPER_H

#include <QObject>
#include <QDebug>
#include "csoundobject.h"


class CsoundWrapper : public QObject
{
    Q_OBJECT
public:
    explicit CsoundWrapper(QObject *parent = 0);
    Q_INVOKABLE void play(QString csd);
    Q_INVOKABLE void setControlChannel(QString channel, double value);
    Q_INVOKABLE double getControlChannel(QString channelName);
    Q_INVOKABLE void stop();
    Q_INVOKABLE void readScore(QString score);
    Q_INVOKABLE void test(QString message) {qDebug()<<"TEST "<<message;}
signals:
    void stateChanged(int state);
private:
    CsoundObject * csObject;
    Csound * cs;

};

#endif // CSOUNDWRAPPER_H

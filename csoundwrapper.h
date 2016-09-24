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
    Q_INVOKABLE void setControlChannel(QString channel, double value); // do I need Q_INVOKABLE, if it is a slot...
    Q_INVOKABLE double getControlChannel(QString channelName); // is channelcausing conflict with webchannel 'channel' in js?
    Q_INVOKABLE void stop();
    Q_INVOKABLE void readScore(QString score);
    Q_INVOKABLE void test(QString message) {qDebug()<<"TEST "<<message;}

    Q_INVOKABLE int getIntValue(QString channelName) {int value = qrand()%100; qDebug()<<"Int C++ value "<<value; return value;}
//    Q_PROPERTY(int intValue READ getIntValue(QString))


signals:
    void stateChanged(int state);
    void newChannelValue(QString channel, double value);
    void testSignal(const QString &text);
public slots:




private:

    CsoundObject * csObject;
    Csound * cs;

};

#endif // CSOUNDWRAPPER_H

#ifndef CSOUNDWRAPPER_H
#define CSOUNDWRAPPER_H

#include <QObject>
#include "csoundobject.h"

class CsoundWrapper : public QObject
{
    Q_OBJECT
public:
    explicit CsoundWrapper(QObject *parent = 0);

    Q_INVOKABLE void play(QString csd);
    Q_INVOKABLE void setChannel(QString channel, double value); // do I need Q_INVOKABLE, if it is a slot...
    Q_INVOKABLE double getChannel(QString channel);
    Q_INVOKABLE void stop();
    Q_INVOKABLE void scoreEvent(QString event);
signals:
    void newScoreEvent(QString event);
    void newChannelValue(QString channel, double value);
    void requestChannelValue(QString channel);

public slots:

private:
    CsoundObject * csObject;
    Csound * cs;

};

#endif // CSOUNDWRAPPER_H

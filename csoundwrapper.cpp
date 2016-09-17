#include "csoundwrapper.h"
#include <QThread>
#include <QApplication>
#include <QDebug>

CsoundWrapper::CsoundWrapper(QObject *parent) : QObject(parent)
{
    csObject = new CsoundObject();
    //cs = csObject->getCsound();

    // Start Csound in separate thread
    QThread * csoundThread = new QThread();
    csObject->moveToThread(csoundThread);

    QObject::connect(csoundThread, &QThread::finished, csObject, &CsoundObject::deleteLater);
    QObject::connect(csoundThread, &QThread::finished, csoundThread, &QThread::deleteLater);
    QObject::connect(QApplication::instance(), &QApplication::aboutToQuit, csObject, &CsoundObject::stop);
    //QObject::connect(csoundThread, &QThread::started, cs, &CsoundObject::play);
    csoundThread->start();

    QObject::connect(this, SIGNAL(newScoreEvent(QString)), csObject, SLOT(scoreEvent(QString)));
    QObject::connect(this, SIGNAL(newChannelValue(QString,double)), csObject, SLOT(setChannel(QString,double)));
    QObject::connect(this, SIGNAL(requestChannelValue(QString)), csObject, SLOT(getChannel(QString)));
}

void CsoundWrapper::play(QString csd)
{
    csObject->setCsd(csd);
    csObject->play();
}

void CsoundWrapper::setChannel(QString channel, double value)
{
    qDebug()<<"CsoundWrapper channel: "<<channel << " value: "<<value;
    emit newChannelValue(channel, value);
}

double CsoundWrapper::getChannel(QString channel)
{
    qDebug()<< "Wrapper request";
    emit requestChannelValue(channel);


}

void CsoundWrapper::stop()
{
    csObject->stop();
}

void CsoundWrapper::scoreEvent(QString event)
{
    qDebug()<<"CsoundWrapper New event: "<<event;
    emit newScoreEvent(event);

}


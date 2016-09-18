#include "csoundwrapper.h"
#include <QThread>
#include <QApplication>
#include <QDebug>


CsoundWrapper::CsoundWrapper(QObject *parent) : QObject(parent)
{
    csObject = new CsoundObject();
    cs = csObject->getCsound();

    // Start Csound in separate thread
    QThread * csoundThread = new QThread();
    csObject->moveToThread(csoundThread);

    QObject::connect(csoundThread, &QThread::finished, csObject, &CsoundObject::deleteLater);
    QObject::connect(csoundThread, &QThread::finished, csoundThread, &QThread::deleteLater);
    QObject::connect(QApplication::instance(), &QApplication::aboutToQuit, csObject, &CsoundObject::stop);
    //QObject::connect(csoundThread, &QThread::started, cs, &CsoundObject::play);
    csoundThread->start();

    QObject::connect(csObject, SIGNAL(statusChanged(int)), this, SIGNAL(stateChanged(int)));

}

void CsoundWrapper::play(QString csd)
{

    csObject->setCsd(csd);
    csObject->play();
}

void CsoundWrapper::setChannel(QString channel, double value)
{
    cs->SetChannel(channel.toLocal8Bit(),value);
}

double CsoundWrapper::getChannel(QString channel)
{
    return cs->GetChannel(channel.toLocal8Bit());
}

void CsoundWrapper::stop()
{
    csObject->stop();
}

void CsoundWrapper::scoreEvent(QString event)
{
    qDebug()<<"CsoundWrapper New event: "<<event;
    cs->InputMessage(event.toLocal8Bit());

}




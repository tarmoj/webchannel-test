#include "csoundwrapper.h"
#include <QThread>
#include <QApplication>


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
}

void CsoundWrapper::play(QString csd)
{
    csObject->setCsd(csd);
    csObject->play();
}

void CsoundWrapper::setChannel(QString channel, double value)
{

}

double CsoundWrapper::getChannel(QString channel)
{

}

void CsoundWrapper::stop()
{
    csObject->stop();
}

void CsoundWrapper::scoreEvent(QString event)
{

}


#include "csoundwrapper.h"
#include <QThread>
#include <QApplication>
#include <QDebug>


CsoundWrapper::CsoundWrapper(QObject *parent) : QObject(parent)
{
    csObject = new CsoundObject();
    cs = csObject->getCsound();

    QObject::connect(QApplication::instance(), &QApplication::aboutToQuit, csObject, &CsoundObject::stop);
    QObject::connect(csObject, SIGNAL(statusChanged(int)), this, SIGNAL(stateChanged(int)));

}

void CsoundWrapper::play(QString csd)
{

    csObject->setCsd(csd);
    csObject->start(); // start playiback in separate thread
}

void CsoundWrapper::setControlChannel(QString channel, double value)
{
    qDebug()<<"CsoundWrapper::setControlChannel  channel: "<< channel << "value: "<<value;
    cs->SetChannel(channel.toLocal8Bit(),value);  // bad practice to access object from another thread, but let it be now...
}

double CsoundWrapper::getControlChannel(QString channel)
{
    double value = cs->GetChannel(channel.toLocal8Bit());
    qDebug()<<"CsoundWrapper::getControlChannel " << channel << " value: " << value;
    emit newChannelValue(channel, value);
    return value;
}

void CsoundWrapper::stop()
{
    csObject->stop();
}

void CsoundWrapper::readScore(QString score)
{
    qDebug()<<"CsoundWrapper::readScore New event: "<<score;
    cs->ReadScore(score.toLocal8Bit());
}





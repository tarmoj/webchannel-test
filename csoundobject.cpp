

#include "csoundobject.h"
#include <QDebug>
#include <QCoreApplication>
#include <QFile>
#include <QTemporaryFile>

CsoundObject::CsoundObject(QObject *parent) : QObject(parent)
{
    cs = new Csound();
    stopNow = false;
    csdFile = "test.csd";

}

void CsoundObject::play() {

    //cs->SetOption("-odac");
    //cs->SetOption("-d");
    QTemporaryFile * tempFile ;//::createNativeFile(csdFile);



   if (csdFile.startsWith(":/")) {
       tempFile = QTemporaryFile::createNativeFile(csdFile);
        if (tempFile)
            csdFile = tempFile->fileName();
    }

    int ret = cs->Compile(csdFile.toLocal8Bit().data()); //cs->CompileOrc(orc.toLocal8Bit());
	if (!ret) {
        emit statusChanged(Playing);
		while (cs->PerformKsmps()==0 && !stopNow) {
            QCoreApplication::processEvents(); // probably bad solution but works. otherwise other slots will never be calles
		}

    } else {
        emit statusChanged(Error);
        cs->Cleanup();
        cs->Reset();
        return;
    }

	qDebug()<<"Stopping csound";
	cs->Stop();
    cs->Cleanup();
    cs->Reset();
	stopNow = false;
    emit statusChanged(Stopped);

}

void CsoundObject::stop() {
	stopNow = true;
}
/*
void CsoundObject::setChannel(QString channel, double value) {
	qDebug()<<"channel: "<<channel << " value: "<<value;
	cs->SetChannel(channel.toLocal8Bit(), value);
}

double CsoundObject::getChannel(QString channel)
{
    double value = cs->GetChannel(channel.toLocal8Bit());
    emit newChannelValue(channel, value);
	qDebug()<<"Value from "<<channel<<" :"<< value;
	return value;
}


void CsoundObject::scoreEvent(QString event)
{
	qDebug()<<"New event: "<<event;
	cs->InputMessage(event.toLocal8Bit());
}
*/

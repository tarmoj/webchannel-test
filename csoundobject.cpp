

#include "csoundobject.h"
#include <QDebug>
#include <QCoreApplication>

CsoundObject::CsoundObject(QObject *parent) : QObject(parent)
{
    cs = new Csound();
    stopNow = false;
    csdFile = "test.csd";

}

void CsoundObject::play() {

	cs->SetOption("-odac");
	cs->SetOption("-d");

    int ret = cs->Compile(csdFile.toLocal8Bit().data()); //cs->CompileOrc(orc.toLocal8Bit());
	if (!ret) {
		cs->Start();

		while (cs->PerformKsmps()==0 && !stopNow) {
			QCoreApplication::processEvents(); // probably bad solution but works. otherwise other slots will never be calles
		}

	}
	qDebug()<<"Stopping csound";
	cs->Stop();
	stopNow = false;

}

void CsoundObject::stop() {
	stopNow = true;
}

void CsoundObject::setChannel(QString channel, double value) {
	qDebug()<<"channel: "<<channel << " value: "<<value;
	cs->SetChannel(channel.toLocal8Bit(), value);
}

double CsoundObject::getChannel(QString channel)
{
	double value = cs->GetChannel("value" );
	qDebug()<<"Value from "<<channel<<" :"<< value;
	return value;
}


void CsoundObject::scoreEvent(QString event)
{
	qDebug()<<"New event: "<<event;
	cs->InputMessage(event.toLocal8Bit());
}

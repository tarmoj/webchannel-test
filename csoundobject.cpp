/*
	Copyright (C) 2016 Tarmo Johannes
	trmjhnns@gmail.com

	This file is part of eClick.

	eClick is free software; you can redistribute it and/or modify it
	under the terms of the GNU GENERAL PUBLIC LICENSE Version 3,
		published by Free Software Foundation, Inc. <http://fsf.org/>

	eClick is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with eClick; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
	02111-1307 USA
*/

#include "csoundobject.h"
#include <QDebug>
#include <QThread>
#include <QCoreApplication>

CsoundObject::CsoundObject(QObject *parent) : QObject(parent)
{
    cs = new Csound();
    stopNow = false;

}

void CsoundObject::play() {

	cs->SetOption("-odac");
	cs->SetOption("-d");

	QString orc =R"(
			sr = 44100
			nchnls = 2
			0dbfs = 1
			ksmps = 32

			chn_k "value",3

			chnset 0.5,"value"

			schedule "test",0,0.5

			instr test
				prints "INSTR TEST"
				kval chnget "value"
				printk2 kval
				kfreq = 300+400*kval
				asig vco2 linen(0.5,0.05,p3,0.1), kfreq
				asig moogvcf asig, 400+600*(1-kval), 0.3+(1-kval)/2
				outs asig, asig
			endin

			;schedule "channelTest",0,-1
			instr channelTest
				kvalue chnget "value"
				printk2 kvalue
			endin


			)";

	int ret = cs->CompileOrc(orc.toLocal8Bit());
	if (!ret) {
		cs->Start();
		cs->SetChannel("value",0.5);

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

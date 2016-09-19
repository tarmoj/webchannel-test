

#include "csoundobject.h"
#include <QDebug>
#include <QCoreApplication>
#include <QFile>
#include <QTemporaryFile>

CsoundObject::CsoundObject()
{
    cs = new Csound();
    stopNow = false;
    csdFile = "test.csd";

}

void CsoundObject::run() {

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
		}

    } else {
        emit statusChanged(Error);
        cs->Cleanup();
        cs->Reset();
        quit(); // finish the trhead
    }

	qDebug()<<"Stopping csound";
	cs->Stop();
    cs->Cleanup();
    cs->Reset();
	stopNow = false;
    emit statusChanged(Stopped);
    quit();

}

void CsoundObject::stop() {
	stopNow = true;
}


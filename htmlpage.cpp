#include "htmlpage.h"
#include <QThread>
#include <QApplication>


HtmlPage::HtmlPage(QWidget *parent) :
   QWebEngineView(parent)
{

	// Start Csound
	cs = new CsoundObject();
	//QThread * csoundThread = new QThread();
	//cs->moveToThread(csoundThread);

//	QObject::connect(csoundThread, &QThread::finished, cs, &CsoundObject::deleteLater);
//	QObject::connect(csoundThread, &QThread::finished, csoundThread, &QThread::deleteLater);
//	QObject::connect(QApplication::instance(), &QApplication::aboutToQuit, cs, &CsoundObject::stop);
//	QObject::connect(csoundThread, &QThread::started, cs, &CsoundObject::play);

	//csoundThread->start();
	cs->play();
	// Set up the communications channel
	this->page()->setWebChannel(&channel) ;
	//channel.registerObject("widget", this) ;
	channel.registerObject("csound", cs) ;

    // Set the page content
    setUrl(QUrl("qrc:/index.html")) ;

}

HtmlPage::~HtmlPage()
{
}

void HtmlPage::event(QString eventString)
{
	qDebug()<<"Call in C++ "<<eventString;

}

void HtmlPage::value2js(QString channel, double value)
{
	QString command = QString("document.getElementById( \"label\").innerHTML = \"%1\" ").arg(value); //QString("newChannelValue(%1,%2,%3,'%4');").arg(sX).arg(sY).arg(sz).arg(colour) ;
	page()->runJavaScript(command) ;
}

void HtmlPage::setChannel(QString channel, double value)
{
	qDebug()<<"Channel"<<channel<<" value: "<<value;

}


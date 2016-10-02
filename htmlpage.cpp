#include "htmlpage.h"


HtmlPage::HtmlPage(QWidget *parent) :
   QWebEngineView(parent)
{
}

HtmlPage::~HtmlPage()
{
}


void HtmlPage::value2js(QString channel, double value)
{
	QString command = QString("document.getElementById( \"label\").innerHTML = \"%1\" ").arg(value); //QString("newChannelValue(%1,%2,%3,'%4');").arg(sX).arg(sY).arg(sz).arg(colour) ;
	page()->runJavaScript(command) ;
}




#ifndef HTMLPAGE_H
#define HTMLPAGE_H

#include <QWidget>
#include <QString>
#include <QtWebEngineWidgets>
#include <QtWebChannel/QtWebChannel>

#include "csoundobject.h"

class HtmlPage : public QWebEngineView
{
    Q_OBJECT
	//Q_PROPERTY(int number READ getNumber WRITE setNumber NOTIFY numChanged)
private:
    QWebChannel channel ;            // Channel for C++ to Javascript comms
    CsoundObject * cs;


signals:
	void numChanged();

public:
    explicit HtmlPage(QWidget *parent = 0);
    virtual ~HtmlPage() ;
	int number;



    Q_INVOKABLE void scoreEvent(QString event);
    Q_INVOKABLE void setChannel(QString channel, double value);
	//Q_INVOKABLE void setNumber(int number) {this->number=number;}
	//Q_INVOKABLE int getNumber() {return this->number;}
public slots:
	void event(QString eventString);
	//void jsUpdated(int x, int y) ;                         // Callback from javascript (save X & Y)
	void value2js(QString channel, double value);
    //void setChannel(QString channel, double value);

signals:
    void cursorMoved(int x, int y) ; // Indicate cursor has moved


};

#endif // HTMLPAGE_H

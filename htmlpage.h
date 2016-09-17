#ifndef HTMLPAGE_H
#define HTMLPAGE_H

#include <QWidget>
#include <QString>
#include <QtWebEngineWidgets>
#include <QtWebChannel/QtWebChannel>

#include "csoundwrapper.h"

class HtmlPage : public QWebEngineView
{
    Q_OBJECT
	//Q_PROPERTY(int number READ getNumber WRITE setNumber NOTIFY numChanged)
private:
    QWebChannel channel ;            // Channel for C++ to Javascript comms
    CsoundWrapper * cs;


signals:
	void numChanged();

public:
    explicit HtmlPage(QWidget *parent = 0);
    virtual ~HtmlPage() ;

public slots:
    void value2js(QString channel, double value);


};

#endif // HTMLPAGE_H

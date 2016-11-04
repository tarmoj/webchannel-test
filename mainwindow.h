#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#ifdef USE_WEBKIT
	#include <QtWebKit>
	#include <QWebView>
	#include <QWebFrame>
	#include <QWebInspector>
#else
	#include <QtWebEngineWidgets>
	#include <QtWebChannel/QtWebChannel>
	#include <QWebEngineView>
#endif


#include <QTemporaryFile>

#include "csoundwrapper.h"



namespace Ui {
class mainWindow;
}

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = 0);
    ~mainWindow();

    void loadCsd();
    QString getHtmlText();
    void updateHtml();

public slots:
    void stateChanged(int state);
#ifdef USE_WEBKIT
	void addJSObject();
#endif
private slots:
    void on_playButton_clicked();
    void on_stopButton_clicked();
    void on_loadButton_clicked();
    void on_updateButton_clicked();

private:
    Ui::mainWindow *ui;
    CsoundWrapper cs; // NB! must be in stack, ie not pointer...
#ifdef USE_WEBKIT
	QWebView * htmlView;
#else
	QWebChannel channel ;            // Channel for C++ to Javascript comms
	QWebEngineView * htmlView;

#endif

	QString csd;
    QTemporaryFile  tempHtml;

};

#endif // MAINWINDOW_H

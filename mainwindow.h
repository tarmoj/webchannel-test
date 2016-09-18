#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtWebEngineWidgets>
#include <QtWebChannel/QtWebChannel>
#include <QWebEngineView>

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

public slots:
    void stateChanged(int state);

private slots:
	//void cursorMoved(int x, int y) ;

	void on_pushButton_clicked();

    void on_playButton_clicked();

    void on_stopButton_clicked();

private:
    Ui::mainWindow *ui;
    CsoundWrapper cs; // NB! must be in stack, ie not pointer...
    QWebChannel channel ;            // Channel for C++ to Javascript comms
    QWebEngineView * view;

};

#endif // MAINWINDOW_H

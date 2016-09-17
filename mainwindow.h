#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtWebEngineWidgets>
#include <QtWebChannel/QtWebChannel>

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

private slots:
	//void cursorMoved(int x, int y) ;

	void on_pushButton_clicked();

    void on_playButton_clicked();

    void on_stopButton_clicked();

private:
    Ui::mainWindow *ui;
    CsoundWrapper * cs;
    QWebChannel channel ;            // Channel for C++ to Javascript comms
};

#endif // MAINWINDOW_H

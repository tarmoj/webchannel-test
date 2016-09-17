#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebEngineView>


mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    QWebEngineView view;
    view.setUrl(QUrl("qrc:/index.html"));
    view.resize(1024, 750);
    view.show();


    cs = new CsoundWrapper();
    view.page()->setWebChannel(&channel);
    //this->page()->setWebChannel(&channel) ;
    channel.registerObject("csound", cs) ;

    // Set the page content
    //setUrl(QUrl("qrc:/index.html")) ;
}

mainWindow::~mainWindow()
{
    delete ui;
}


void mainWindow::on_pushButton_clicked()
{
    ui->widgetHtmlPage->value2js("value",qrand()%100);
}

void mainWindow::on_playButton_clicked()
{
    cs->play("test.csd");
}

void mainWindow::on_stopButton_clicked()
{
    cs->stop();
}

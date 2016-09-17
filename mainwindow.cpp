#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebEngineView>


mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    QWebEngineView * view = new QWebEngineView();
    view->setUrl(QUrl("qrc:/index.html"));
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->verticalLayout->addWidget(view);
    //view->resize(400, 500);



    cs = new CsoundWrapper();
    view->page()->setWebChannel(&channel);
    channel.registerObject("csound", cs) ;
    cs->getChannel("testChannel");

    // Set the page content
    //setUrl(QUrl("qrc:/index.html")) ;
}

mainWindow::~mainWindow()
{
    delete ui;
}


void mainWindow::on_pushButton_clicked()
{
    qDebug()<<"request channel value";
    cs->getChannel("testValue");
    //ui->widgetHtmlPage->value2js("value",qrand()%100);
}

void mainWindow::on_playButton_clicked()
{
    cs->play("test.csd");
}

void mainWindow::on_stopButton_clicked()
{
    cs->stop();
}

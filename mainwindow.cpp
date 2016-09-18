#include "mainwindow.h"
#include "ui_mainwindow.h"



mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    view = new QWebEngineView();
    view->setUrl(QUrl("qrc:/index.html"));
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->verticalLayout->addWidget(view);
    //view->resize(400, 500);



    //cs = new CsoundWrapper();
    view->page()->setWebChannel(&channel);
    channel.registerObject("csound", &cs) ;

    QObject::connect(&cs, SIGNAL(stateChanged(int)), this, SLOT(stateChanged(int)));
}

mainWindow::~mainWindow()
{
    delete ui;
}

void mainWindow::stateChanged(int state)
{
    QStringList states = QStringList()<< "PLAYING" << "STOPPED"  <<"ERROR";
    qDebug()<<" new state: " << states[state];
    QString command = QString("document.getElementById( \"label\").innerHTML = \"%1\" ").arg(states[state]); // C++ to JavasCript
    view->page()->runJavaScript(command) ;
}


void mainWindow::on_pushButton_clicked()
{

    double value = cs.getChannel("testChannel");
    qDebug()<<"request channel value" << value;
    QString command = QString("document.getElementById( \"label\").innerHTML = \"%1\" ").arg(value); //QString("newChannelValue(%1,%2,%3,'%4');").arg(sX).arg(sY).arg(sz).arg(colour) ;
    view->page()->runJavaScript(command) ;
}

void mainWindow::on_playButton_clicked()
{
    cs.play(":/test.csd"); // TODO: qrc
}

void mainWindow::on_stopButton_clicked()
{
    cs.stop();
}

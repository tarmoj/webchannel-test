#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>



mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    QLabel * label = new QLabel("UUS");
    ui->verticalLayout->addWidget(label);

    view = new QWebEngineView();
    view->setUrl(QUrl("qrc:/index.html"));
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //view->resize(400, 500);

    ui->htmlLayout->addWidget(view);


    csd = ":/test.csd";
    loadFile();
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


//void mainWindow::on_pushButton_clicked()
//{

//    double value = cs.getChannel("testChannel");
//    qDebug()<<"request channel value" << value;
//    QString command = QString("document.getElementById( \"label\").innerHTML = \"%1\" ").arg(value); //QString("newChannelValue(%1,%2,%3,'%4');").arg(sX).arg(sY).arg(sz).arg(colour) ;
//    view->page()->runJavaScript(command) ;
//}

void mainWindow::on_playButton_clicked()
{
    cs.play(csd);
}

void mainWindow::on_stopButton_clicked()
{
    cs.stop();
}

void mainWindow::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home/tarmo/tarmo/csound",
                                                    tr("Csound files (*.csd)"));
    if (fileName.endsWith(".csd")) {
        csd = fileName;
        loadFile();
    }
}

void mainWindow::loadFile()  {
    QFile csdFile(csd);
    if (!csdFile.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        qDebug()<< "Could not open "<<csd;
    }
    ui->csdTextEdit->document()->setPlainText(csdFile.readAll() );

}

void mainWindow::on_updateButton_clicked()
{

}

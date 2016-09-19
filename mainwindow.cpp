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

    htmlView = new QWebEngineView();
    htmlView->setUrl(QUrl("qrc:/index.html"));
    htmlView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //htmlView->resize(400, 500);

    ui->htmlLayout->addWidget(htmlView);


    csd = ":/test.csd";
    loadCsd();
    //cs = new CsoundWrapper();
    htmlView->page()->setWebChannel(&channel);
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
    htmlView->page()->runJavaScript(command) ;
}

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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                                    tr("Csound files (*.csd)"));
    if (fileName.endsWith(".csd")) {
        csd = fileName;
        loadCsd();
    }
}

void mainWindow::loadCsd()  {
    QFile csdFile(csd);
    if (!csdFile.open(QIODevice::ReadOnly | QIODevice::Text) ) {
        qDebug()<< "Could not open "<<csd;
    }
    ui->csdTextEdit->document()->setPlainText(csdFile.readAll() );
    ui->csdTextEdit->moveCursor(QTextCursor::Start);
    qDebug()<<"HTML text: " << getHtmlText();
    updateHtml();
}

QString mainWindow::getHtmlText()
{
    QString htmlText;
    QString text = ui->csdTextEdit->document()->toPlainText();
    if (text.contains("<html")) {
        int startIndex = text.indexOf("<html");
        int endIndex = text.indexOf("</html");
        htmlText = text.mid(startIndex, endIndex-startIndex+7);// + 7 is for  </html>    }
    }

    return htmlText;
}

void mainWindow::updateHtml()
{
    QString htmlText = getHtmlText();
    if (htmlText.isEmpty()) {
        qDebug()<< "<CsHtml5> not found";
        return;
    }

    if (tempHtml.open()) {
        tempHtml.write(htmlText.toLocal8Bit());
        tempHtml.close();
        htmlView->setUrl(QUrl::fromLocalFile(tempHtml.fileName()));
    }

}

void mainWindow::on_updateButton_clicked()
{
    updateHtml();
}

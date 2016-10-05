#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>



mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);

//    QLabel * label = new QLabel("UUS");
//    ui->verticalLayout->addWidget(label);
#ifdef USE_WEBKIT
	htmlView = new QWebView();
#else
	htmlView = new QWebEngineView();
#endif


    //htmlView->resize(400, 500);
	htmlView->setUrl(QUrl("qrc:/test.html"));
	//? htmlView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->htmlLayout->addWidget(htmlView);


    csd = ":/test.csd";
	loadCsd();

#ifdef USE_WEBKIT
	htmlView->page()->mainFrame()->addToJavaScriptWindowObject("csound", &cs);

	// add javascript inspector -  open with right click on htmlview
	htmlView->page()->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

	QWebInspector inspector;
	inspector.setPage(htmlView->page());
	inspector.setVisible(true);
#else
	htmlView->page()->setWebChannel(&channel);
	channel.registerObject("csound", &cs) ;
#endif


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
#ifdef USE_WEBKIT
	htmlView->page()->mainFrame()->evaluateJavaScript(command);
#else
	htmlView->page()->runJavaScript(command) ; // access and change the html page via javascript
#endif

    // the js page could also handle signals from the attachedd C++ object see http://doc.qt.io/qt-5/qtwebchannel-javascript.html
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
	//qDebug()<<"HTML text: " << getHtmlText();
	//updateHtml();
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
        qDebug()<< "<html> tag not found";
        return;
    }

    if (tempHtml.open()) {
        // add necessary lines to load qtwebchannel/qwebchannel.js and qtcsound.js
        // TODO: take care if html includes <head ...something...>
#ifndef USE_WEBKIT
        QString replaceString = "<head> \
                    <script type=\"text/javascript\" src=\"qrc:///qtwebchannel/qwebchannel.js\"> </script> \
                    <script type=\"text/javascript\" src=\"qrc:///qtcsound.js\"></script> ";


        htmlText = htmlText.replace("<head>", replaceString);
        qDebug()<<"Replaced html: " <<htmlText;
#endif
        tempHtml.write(htmlText.toLocal8Bit());
        tempHtml.close();
        htmlView->setUrl(QUrl::fromLocalFile(tempHtml.fileName()));
    }

}

void mainWindow::on_updateButton_clicked()
{
    updateHtml();
}

// TODO: catch javascript console output. See http://doc.qt.io/qt-5/qwebenginepage.html#javaScriptConsoleMessage

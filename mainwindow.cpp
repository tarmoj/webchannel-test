#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

//
// This program has a widget with its own class (HtmlPage) based on QWebEngine
// The HtmlPage calls up a single html file, which contains JavaScript
//
// The Javascript has a handler which places a large dot when the cursor is clicked
// The Javascript then calls (asynchronously) a C++ function
// The C++ function emits a message to the mainwindow to update the X and Y coordinates on the form
// The C++ function then calls (asynchronously) the Javascript to place a small dot at the same X and Y coordinates
//

mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);
}

mainWindow::~mainWindow()
{
    delete ui;
}


void mainWindow::on_pushButton_clicked()
{
	ui->widgetHtmlPage->value2js("value",99.99);
}

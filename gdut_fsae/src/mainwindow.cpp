#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtXlsx>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    setAttribute(Qt::WA_QuitOnClose, false);
//    QXlsx::Document xlsx;
//    xlsx.write("A1", "Hello Qt!");
//    xlsx.saveAs("Test.xlsx");
    qDebug() << "Start the gdut_fsae_plugin";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rec_Msg(QByteArray msg)
{
    qDebug() << msg;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit windows_Close("gdut_fsae_plugin");
}

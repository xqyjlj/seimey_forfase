#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtXlsx>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    setAttribute(Qt::WA_QuitOnClose, false);
    ui->lineE_pga_distance->setValidator(new QDoubleValidator(0, 19999, 2, this));
    create_floder();
    LOG_DEBUG << QString("启动GDUT_FSAE插件");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rec_msg(QByteArray msg)
{
    if (msg.size() >= 4)
    {
        if (msg.data()[0] == 0x01)
        {
            gate_speed_get(msg);
        }
    }
}
void MainWindow::create_floder(void)
{
    QString qs_dir = QDir::currentPath() + "/.workspace" + "/.plugin" + "/.gdut_fsae";

    QDir _dir(qs_dir);
    if (!_dir.exists())
    {
        _dir.mkdir(qs_dir);
    }
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!ui->lineE_pga_drivername->text().isEmpty() && !ui->lineE_pga_carnum->text().isEmpty())
    {
        QString dlgTitle = "提示";
        QString strInfo = "由于你填写了车手信息与赛车编号，你是否希望保存本次数据";
        QMessageBox::StandardButton result;//返回选择的按钮
        result = QMessageBox::question(this, dlgTitle, strInfo,
                                       QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (result == QMessageBox::Yes)
        {
            save_excel();
        }
        else if (result == QMessageBox::No)
        {
        }
        else if (result == QMessageBox::Cancel)
        {
            event->ignore();
            return;
        }
        else
        {
            event->ignore();
            return;
        }

//        QXlsx::Document xlsx;
//        xlsx.write("A1", "Hello Qt!");
//        xlsx.saveAs("Test.xlsx");
    }
    event->accept();
    emit windows_close("gdut_fsae_plugin");
}

void MainWindow::gate_speed_get(QByteArray msg)
{
    uint16_t turns = 0;
    uint32_t millisecond = 0;
    uint16_t crc = 0;
    double distance = 0;
    double speed;
    if (msg.size() == 9)
    {
        uint8_t *char_msg = (uint8_t *)msg.data();
        crc = ((uint16_t)char_msg[7] << 8) | char_msg[8];
        if (crc == c_Gdut_Fsae_Crc->crc16_modbus_table((uint8_t *) char_msg, 7))
        {
            turns = ((uint16_t)char_msg[1] << 8) | char_msg[2];
            millisecond = ((uint32_t)char_msg[3] << 24) | ((uint32_t)char_msg[4] << 16) | ((uint32_t)char_msg[5] << 8) | char_msg[6];
            QTreeWidgetItem *child = new QTreeWidgetItem();
            distance = (uint32_t)ui->lineE_pga_distance->text().toDouble();
            if (distance != 0)
            {
                speed = ((distance * 1000) / millisecond);
                child->setText(1, QString::number(speed));
                ui->waveC_pga_speed->addData(speed);
            }
            child->setText(0, QString::number(turns));
            child->setText(2, QString::number(millisecond));
            ui->tree_pga_info->addTopLevelItem(child);
        }
    }
}

void MainWindow::on_comLB_pga_clear_pressed()
{
    QByteArray msg;
    msg.resize(6);
    msg[0] = 0xAA;
    msg[1] = 0x02;
    msg[2] = 0x00;
    msg[3] = 0x80;
    msg[4] = 0x50;
    msg[5] = 0x0D;
    emit send_msg(msg);
}

void MainWindow::save_excel(void)
{
    QString dlgTitle = "光电门数据保存";
    QString txtLabel = "请输入文件名，不需要输入后缀";
    QString defaultInput = "数据1";
    QLineEdit::EchoMode echoMode = QLineEdit::Normal; //正常文字输入
    //QLineEdit::EchoMode echoMode=QLineEdit::Password;//密码输入
    bool ok = false;
    QString msg = QInputDialog::getText(this, dlgTitle, txtLabel, echoMode, defaultInput, &ok, Qt::MSWindowsFixedSizeDialogHint);
    if (ok && !msg.isEmpty())
    {
        msg += QString(".xlsx");
    }
    QString filename = QDir::currentPath() + "/.workspace" + "/.plugin" + "/.gdut_fsae" + "/" + msg;

    QXlsx::Document xlsx;
    xlsx.write("A1", QString("车手姓名"));
    xlsx.write("B1", QString("赛车编号"));
    xlsx.write("C1", QString("练车地点"));
    xlsx.write("D1", QString("赛道布置"));
    xlsx.write("E1", QString("赛道情况"));
    xlsx.write("F1", QString("路程"));
    xlsx.write("G1", QString("圈数"));
    xlsx.write("H1", QString("速度"));
    xlsx.write("I1", QString("时间"));

    xlsx.write("A2", ui->lineE_pga_drivername->text());
    xlsx.write("B2", ui->lineE_pga_carnum->text());
    xlsx.write("C2", ui->lineE_pga_place->text());
    xlsx.write("D2", ui->lineE_pga_layout->text());
    xlsx.write("E2", ui->lineE_pga_situation->text());
    xlsx.write("G2", ui->lineE_pga_distance->text());
    xlsx.saveAs(filename);
}

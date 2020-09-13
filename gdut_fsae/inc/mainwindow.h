#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QByteArray>
#include <QMouseEvent>
#include "gdut_fsae_crc.h"

#define LOG_DEBUG qDebug()<<"gdut_fsae_plugin:"
namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public:
    void rec_msg(QByteArray msg);
protected:
    virtual void closeEvent(QCloseEvent *event);
signals:
    void send_msg(QByteArray msg);
    void windows_close(QString msg);
private slots:
    void on_comLB_pga_clear_pressed();

private:
    void gate_speed_get(QByteArray msg);
    void save_excel(void);
    void create_floder(void);
private:
    Ui::MainWindow *ui;
    gdut_fsae_crc *c_Gdut_Fsae_Crc = new gdut_fsae_crc(this);

};

#endif // MAINWINDOW_H

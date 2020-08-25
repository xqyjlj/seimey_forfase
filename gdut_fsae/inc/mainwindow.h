#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QByteArray>
#include <QMouseEvent>
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
    void rec_Msg(QByteArray msg);
protected:
    virtual void closeEvent(QCloseEvent *event);
signals:
    void windows_Close(QString msg);
private:
    Ui::MainWindow *ui;
    QString _data;
};

#endif // MAINWINDOW_H

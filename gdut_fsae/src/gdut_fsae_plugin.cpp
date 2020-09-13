#include "gdut_fsae_plugin.h"

gdut_fsae_plugin::gdut_fsae_plugin(QObject *parent) : QObject(parent)
{

}

void gdut_fsae_plugin::show()
{
    w = new MainWindow();
    w->show();
    connect(w, SIGNAL(windows_close(QString)), this, SLOT(close_event(QString)), Qt::UniqueConnection);
    connect(w, SIGNAL(send_msg(QByteArray)), this, SLOT(forward_msg(QByteArray)), Qt::UniqueConnection);
}

void gdut_fsae_plugin::rec_msg(QByteArray msg)
{
    w->rec_msg(msg);
}

void gdut_fsae_plugin::close_event(QString msg)
{
    emit plugin_close(msg);
}

void gdut_fsae_plugin::forward_msg(QByteArray msg)
{
    emit send_msg(msg);
}

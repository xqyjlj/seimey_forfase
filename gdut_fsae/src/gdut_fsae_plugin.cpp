#include "gdut_fsae_plugin.h"

gdut_fsae_plugin::gdut_fsae_plugin(QObject *parent) : QObject(parent)
{

}

void gdut_fsae_plugin::show()                            // 显示窗口
{
    w = new MainWindow();
    w->show();
    connect(w, SIGNAL(windows_Close(QString)), this, SLOT(close_Event(QString)), Qt::UniqueConnection);
}

void gdut_fsae_plugin::rec_Msg(QString msg)
{
    w->rec_Msg(msg.toLatin1());
}

void gdut_fsae_plugin::close_Event(QString msg)
{
    emit plugin_Close(msg);
}

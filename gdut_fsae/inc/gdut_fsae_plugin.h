#ifndef GDUT_FSAE_PLUGIN_H
#define GDUT_FSAE_PLUGIN_H

#include <QObject>
#include "gdut_fsae_interface.h"
#include "mainwindow.h"

class gdut_fsae_plugin : public QObject, public gdut_fsae_interface
{
    Q_OBJECT

    Q_INTERFACES(gdut_fsae_interface)                         /*  Q_INTERFACES宏用于告诉Qt该类实现的接口。 */
    Q_PLUGIN_METADATA(IID gdut_fsae_interface_iid)            /*  Q_PLUGIN_METADATA宏用于描述插件元数据 */

public:
    explicit gdut_fsae_plugin(QObject *parent = nullptr);

    virtual void rec_msg(QByteArray msg) ;          /* 接收到来自插件管理器的消息 */
    virtual void show();                        /*  显示窗口 */
signals:
    void send_msg(QByteArray msg);
    void plugin_close(QString msg);
private slots:
    void close_event(QString msg);
    void forward_msg(QByteArray msg);
private:
    MainWindow *w;

};

#endif // GDUT_FSAE_PLUGIN_H

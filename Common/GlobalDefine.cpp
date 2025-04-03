#include "GlobalDefine.h"

#include <QLineEdit>
#include <QSettings>

const QSettings gSettings("./configs/config.ini", QSettings::IniFormat);

void UIHelper::RePolish(QWidget* TargetWgt) {
    //取消style状态之后再填入状态
    TargetWgt->style()->unpolish(TargetWgt);
    TargetWgt->style()->polish(TargetWgt);
}
void UIHelper::SetLineEditError(QLineEdit* Target, bool IsError)
{
    if(!Target|| !Target->isVisible())
    {
        return;
    }
    Target->setProperty("error", IsError);
    Target->style()->unpolish(Target);
    Target->style()->polish(Target);
}
;

const QString& Net::UrlHome()
{
    // 读取键值，第二个参数为默认值（若键不存在）
    static QString Host = gSettings.value("GateServer/host"/*, "localhost"*/).toString();

    return Host;
}

const QString& Net::NetPort()
{
    static QString Port = gSettings.value("GateServer/port"/*, "9527"*/).toString();

    return Port;
}

const QString& Net::RequestMain()
{
    static QString MainUrl = QString("%1%2:%3/").arg(UrlBegin).arg(Net::UrlHome()).arg(Net::NetPort());
        //Net::UrlBegin + "://" + Net::UrlHome() + ":" + Net::NetPort + "/";
    return MainUrl;
}

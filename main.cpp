﻿#include <QApplication>
#include <QFile>
#include <QResource>

#include "Common/TcpMgr.h"
#include "Widgets/ReqApplyFriend.h"
#include "Widgets/mainwindow.h"
#include "Widgets/MainChatWgt.h"



// 设置全局样式表
void SetTotalQss(QApplication& A)
{
    QFile qssFile(":/Skin/StylesSheet.qss");
    qssFile.open(QFile::ReadOnly);

	A.setStyleSheet(qssFile.readAll());
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /** 加载rcc资源包
     *    - 多个rcc可同时加载，同名路径后加载覆盖旧的加载
     *    - rcc常驻内存，如果某个过大，可考虑分割加载卸载
     */
    QResource::registerResource("Resource/Assets.rcc");

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    SetTotalQss(a);

    MainWindow w;
    QObject::connect(&STcpMgr::GetInstance(), &STcpMgr::sigSwitchChatWgt, [&w]()
    {
	    w.close();
	    WChatWgt::GetIns().GetUI()->show();
    });

    w.show();

    return a.exec();
}

#include <QApplication>
#include <QFile>
#include <QResource>
#include "Widgets/mainwindow.h"

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

    // 设置全局样式表
    QFile qssFile(":/Skin/StylesSheet.qss");
    qssFile.open(QFile::ReadOnly);
    a.setStyleSheet(qssFile.readAll());
    MainWindow w;
    w.show();
    return a.exec();
}

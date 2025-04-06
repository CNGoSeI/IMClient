#ifndef WIDGETFILESHELPER_H
#define WIDGETFILESHELPER_H
#include <QUiLoader>
#include <QFile>
#include <QDebug>
#include <QString>

namespace WgtFile
{
	const inline QString WgtFileRoot{":/Skin/"};
	const QString MaingWndPath = WgtFileRoot + "MainWnd.ui";
	const QString LoginDlgPath = WgtFileRoot + "LoginDialog.ui";
	const QString RegDlgPath = WgtFileRoot+"Registerdialog.ui";//注册界面
	const QString RestPasswd = WgtFileRoot + "ResetPwdWgt.ui";//重设密码界面

	inline QWidget* LoadUI(const QString& UIFile, QWidget* parent = nullptr)
	{
        QUiLoader loader;
        qDebug() << "文件名：" << UIFile;
        QFile file(UIFile);
        return loader.load(&file, parent);
	}
}

#endif
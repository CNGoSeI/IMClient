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
	const QString MainChatUI = WgtFileRoot + "ChatWgt.ui";//聊天主界面
	const QString ChatUserItem = WgtFileRoot + "Chatuserwid.ui";//聊天界面消息模式用户消息框
	const QString CloseTitle = WgtFileRoot + "CloseTitle.ui";
	const QString LoadingWgt = WgtFileRoot + "Loading.ui";
	const QString ChatPageWgt = WgtFileRoot + "ChatPage.ui";
	const QString ChatDataArea = WgtFileRoot + "ChatArea.ui";
	const QString SelfMsgItem = WgtFileRoot + "MessageItemSelf.ui";
	const QString OtherMsgItem = WgtFileRoot + "MessageItemOther.ui";
	const QString AddUserItem = WgtFileRoot + "AddUserItem.ui";

	inline QWidget* LoadUI(const QString& UIFile, QWidget* parent = nullptr)
	{
        QUiLoader loader;
        qDebug() << "文件名：" << UIFile;
        QFile file(UIFile);
        return loader.load(&file, parent);
	}
}

#endif
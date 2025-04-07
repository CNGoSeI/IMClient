#include "LoginDlg.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"
#include "Common/HttpMgr.h"
#include "Common/PublicFun.h"

DLoginDialog::DLoginDialog(QWidget* parent):
WLoadUIWgtBase::WLoadUIWgtBase(WgtFile::LoginDlgPath, parent)
{
	InitHttpHandlers();
}

DLoginDialog::~DLoginDialog()
{
}

void DLoginDialog::InitControls()
{
	Btn_Reg = UI->findChild<QPushButton*>("Btn_Reg");
	Q_ASSERT(Btn_Reg != nullptr);

	Btn_Login = UI->findChild<QPushButton*>("Btn_Login");
	Q_ASSERT(Btn_Login != nullptr);

	Lab_MsgTip = UI->findChild<QLabel*>("Lab_MsgTip");
	Q_ASSERT(!Lab_MsgTip);
	Lab_MsgTip->clear();

	Edt_User = UI->findChild<QLineEdit*>("Edt_User");
	Q_ASSERT(!Edt_User);

	Edt_Passwd = UI->findChild<QLineEdit*>("Edt_Passwd");
	Q_ASSERT(!Edt_Passwd);

	Lab_MsgTip->setProperty("state", "normal");//设置属性状态，QSS存在指定
	
}

void DLoginDialog::ConnectSigSlot()
{
	connect(Btn_Reg, &QPushButton::clicked, this, &DLoginDialog::sigSwitchRegister);

	connect(Btn_Login, &QPushButton::clicked, this, [this]()
	{
		if(IsAllEdtInputMatch())
		{
			Btn_Login->setEnabled(false);
			auto user = Edt_User->text();
			auto pwd = Edt_Passwd->text();
			//发送http请求登录
			QJsonObject json_obj;
			json_obj["user"] = user;
			json_obj["passwd"] = Tool::EcryptionStr(pwd);
			SHttpMgr::GetInstance().PostHttpReq(QUrl(Net::RequestMain() +Net::URI_USER_LOGIN),
				json_obj, ReqID::ID_LOGIN_USER, Modules::LOGINMOD);
		}
	});

	connect(&SHttpMgr::GetInstance(), &SHttpMgr::sigLoginModFinish, this,&DLoginDialog::slotLoginFinish);
}

void DLoginDialog::SetControlsToNormal()
{
	Lab_MsgTip->clear();
	SetEditeLinesEnabale(true);
	SetEditeLinesToNormal();

	Btn_Login->setEnabled(true);
}

bool DLoginDialog::IsAllEdtInputMatch()
{
	SetEditeLinesToNormal();
	Lab_MsgTip->clear();

	if (!Tool::IsUserNameMatch(Edt_User->text()))
	{
		UIHelper::SetTipState(Lab_MsgTip, "请输入6位以上的用户名", false);
		UIHelper::SetLineEditError(Edt_User, true);
		return false;
	}

	if (!Tool::IsPasswdMatch(Edt_Passwd->text()))
	{
		UIHelper::SetTipState(Lab_MsgTip, "请输入8位以上的密码，必须存在大小写字母", false);
		UIHelper::SetLineEditError(Edt_Passwd, true);
		return false;
	}

	return true;
}

void DLoginDialog::SetEditeLinesEnabale(bool bEnable)
{

	Edt_User->setEnabled(bEnable);
	Edt_Passwd->setEnabled(bEnable);
}

void DLoginDialog::SetEditeLinesToNormal()
{

	UIHelper::SetLineEditError(Edt_User);
	UIHelper::SetLineEditError(Edt_Passwd);

}

void DLoginDialog::InitHttpHandlers()
{
	Handlers.emplace(ReqID::ID_LOGIN_USER, [this](QJsonObject jsonObj)
	{
		int error = jsonObj["error"].toInt();
		if (error != ErrorCodes::SUCCESS)
		{
			UIHelper::SetTipState(Lab_MsgTip, ErrorCodes::GetErrorStr(error), false);
			return;
		}
		auto user = jsonObj["user"].toString();
		UIHelper::SetTipState(Lab_MsgTip, tr("登陆成功！"), true);
		qDebug() << "用户登录 User: " << user;
	});

}

void DLoginDialog::slotLoginFinish(const int ReqId, const QString& Res, const int ErrCode)
{
	Btn_Login->setEnabled(true);

	QJsonObject jsonObj;
	if (!Tool::ParserResponJson(Res, jsonObj, ErrCode))
	{
		UIHelper::SetTipState(Lab_MsgTip, ErrorCodes::GetErrorStr(ErrCode), false);
	}

	//调用对应的逻辑
	if (Handlers.find(ReqId) == Handlers.end())
	{
		UIHelper::SetTipState(Lab_MsgTip, tr("登录收到返回，但未找到对应方法: %1").arg(ReqId), false);
		qDebug("登录请求的返回，未找到对应的执行方法！ID:%d", ReqId);
		return;
	}

	Handlers[ReqId](jsonObj);

}

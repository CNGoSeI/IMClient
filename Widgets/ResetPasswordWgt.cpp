#include "ResetPasswordWgt.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"
#include "Common/HttpMgr.h"
#include <Common/PublicFun.h>

WResetPasswordWgt::WResetPasswordWgt(QWidget* parent) :
	ILoadUIWgtBase(WgtFile::RestPasswd, parent)
{
	InitHttpHandlers();
}

void WResetPasswordWgt::InitControls()
{
	Btn_Ok = UI->findChild<QPushButton*>("Btn_Ok");
	Q_ASSERT(Btn_Ok != nullptr);

	Edt_Password = UI->findChild<QLineEdit*>("Edt_Paswd");
	Q_ASSERT(Edt_Password != nullptr);

	Lab_MsgTip = UI->findChild<QLabel*>("Lab_MsgTip");
	Q_ASSERT(Lab_MsgTip != nullptr);

	Edt_Email = UI->findChild<QLineEdit*>("Edt_Email");
	Q_ASSERT(Edt_Email);

	Edt_User = UI->findChild<QLineEdit*>("Edt_User");
	Q_ASSERT(Edt_User);

	Edt_Verify = UI->findChild<QLineEdit*>("Edt_Verify");
	Q_ASSERT(Edt_Verify);

	Btn_GetCode = UI->findChild<QPushButton*>("Btn_GetCode");
	Q_ASSERT(Btn_GetCode);

	Btn_SwitchPwdShow=UI->findChild<QPushButton*>("Btn_SwitchPwdShow");
	Q_ASSERT(Btn_SwitchPwdShow);

	Lab_MsgTip->setProperty("state", "normal");//设置属性状态，QSS存在指定

	SetControlsToNormal();
}

void WResetPasswordWgt::ConnectSigSlot()
{
	connect(Btn_SwitchPwdShow, &QPushButton::toggled, [this](bool checked)
	{
		Edt_Password->setEchoMode(checked? QLineEdit::Password : QLineEdit::Normal);
	});

	connect(Btn_GetCode, &QPushButton::clicked, this, [this]()
	{
		SetEdtControlsState();
		if (IsAllEdtInputMatch())
		{
			Btn_GetCode->setEnabled(false);
			SetEdtControlsEnable(false);
			//发送http请求获取验证码
			const auto email = Edt_Email->text();
			QJsonObject json_obj;
			json_obj["email"] = email;
			SHttpMgr::GetInstance().PostHttpReq(QUrl(Net::RequestMain() + Net::URI_GET_VERIFICATION),
			                                    json_obj, ReqID::ID_GET_VARIFY_CODE, Modules::RESETMOD);
			return;
		}

	});

	connect(Btn_Ok, &QPushButton::clicked, this, [this]()
	{
		//发送http重置用户请求
		if (IsAllEdtInputMatch())
		{
			QJsonObject json_obj;
			json_obj["user"] = Edt_User->text();
			json_obj["email"] = Edt_Email->text();
			json_obj["passwd"] = Tool::EcryptionStr(Edt_Password->text());
			json_obj["varifycode"] = Edt_Verify->text();
			SHttpMgr::GetInstance().PostHttpReq(QUrl(Net::RequestMain() + Net::URI_RESET_PWD),
			                                    json_obj, ReqID::ID_RESET_PWD, Modules::RESETMOD);
			Btn_Ok->setEnabled(false);
		}
	});

	connect(&SHttpMgr::GetInstance(), &SHttpMgr::sigResetPwdModFinish, this, &WResetPasswordWgt::slotRegModFinish);
}

void WResetPasswordWgt::InitHttpHandlers()
{
	Handlers.emplace(ReqID::ID_GET_VARIFY_CODE, [this](const QJsonObject& JsonObj)
	{
		int Error = JsonObj["error"].toInt();
		if (Error != ErrorCodes::SUCCESS)
		{
			UIHelper::SetTipState(Lab_MsgTip, ErrorCodes::GetErrorStr(Error), false);
			SetEdtControlsEnable(true);
			Btn_GetCode->setEnabled(true);
			Btn_Ok->setEnabled(true);
			return;
		}

		//显示消息，保持禁用无关编辑控件
		auto Email = JsonObj["email"].toString();
		UIHelper::SetTipState(Lab_MsgTip, tr("验证码已发送到邮箱，注意查收"), true);
		Btn_Ok->setEnabled(true);
		SetEdtControlsEnable(false);
	});

	//重置密码回复
	Handlers.emplace(ReqID::ID_RESET_PWD, [this](QJsonObject jsonObj)
	{
		int error = jsonObj["error"].toInt();
		if (error != ErrorCodes::SUCCESS)
		{
			UIHelper::SetTipState(Lab_MsgTip, ErrorCodes::GetErrorStr(error), false);
			Btn_Ok->setEnabled(false);//更改输入之后再能点击
			Btn_GetCode->setEnabled(true);
			SetEdtControlsEnable(true);

			return;
		}
		auto email = jsonObj["email"].toString();
		UIHelper::SetTipState(Lab_MsgTip, tr("重置成功,点击返回登录"), true);
		qDebug() << "email is " << email;
		qDebug() << "user uuid is " << jsonObj["uuid"].toString();
	});
}

bool WResetPasswordWgt::IsAllEdtInputMatch()
{
	if (!Tool::IsUserNameMatch(Edt_User->text()))
	{
		UIHelper::SetTipState(Lab_MsgTip, "请输入6位以上的用户名", false);
		UIHelper::SetLineEditError(Edt_User, true);
		return false;
	}

	if (Edt_Email->text().isEmpty() || !Tool::IsStrMatchEmail(Edt_Email->text()))
	{
		UIHelper::SetTipState(Lab_MsgTip, "邮箱格式不正确", false);
		UIHelper::SetLineEditError(Edt_Email, true);
		return false;
	}

	if (!Tool::IsPasswdMatch(Edt_Password->text()))
	{
		UIHelper::SetTipState(Lab_MsgTip, "请输入8位以上的密码，必须存在大小写字母", false);
		UIHelper::SetLineEditError(Edt_Password, true);
		return false;
	}

	Lab_MsgTip->clear();
	SetEdtControlsState();
	return true;
}

void WResetPasswordWgt::SetControlsToNormal()
{

	Lab_MsgTip->clear();
	Btn_SwitchPwdShow->setChecked(true);
	Edt_Password->setEchoMode(QLineEdit::Password);

	Btn_GetCode->setEnabled(true);
	Btn_Ok->setEnabled(true);

	SetEdtControlsState(false);

	Edt_User->clear();
	Edt_Email->clear();
	Edt_Password->clear();
	Edt_Verify->clear();

	Edt_Email->setEnabled(true);
	Edt_User->setEnabled(true);
	Edt_Password->setEnabled(true);
	Edt_Verify->setEnabled(true);


}

void WResetPasswordWgt::SetEdtControlsState(const bool bIsError)
{
	UIHelper::SetLineEditError(Edt_Email, bIsError);
	UIHelper::SetLineEditError(Edt_User, bIsError);
	UIHelper::SetLineEditError(Edt_Password, bIsError);
	UIHelper::SetLineEditError(Edt_Verify, bIsError);

}

void WResetPasswordWgt::SetEdtControlsEnable(const bool bEnable)
{
	if (Edt_User)Edt_User->setEnabled(bEnable);
	if (Edt_Email)Edt_Email->setEnabled(bEnable);
	if (Edt_Password)Edt_Password->setEnabled(bEnable);
}

void WResetPasswordWgt::slotRegModFinish(const int ReqID, const QString& Res, const int ErrCode)
{
	Btn_Ok->setEnabled(true);

	QJsonObject jsonObj;
	if (!Tool::ParserResponJson(Res, jsonObj, ErrCode))
	{
		UIHelper::SetTipState(Lab_MsgTip, ErrorCodes::GetErrorStr(ErrCode), false);
	}


	const auto it = Handlers.find(ReqID);
	if(it==Handlers.end())
	{

		UIHelper::SetTipState(Lab_MsgTip, tr("重置密码获取返回，但未找到对应方法: %1").arg(ReqID), false);
		qDebug("重置密码请求返回，未找到对应的执行方法！ID:%d", ReqID);
		return;
	}

	it->second(jsonObj);
}

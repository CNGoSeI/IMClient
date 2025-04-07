#include "RegisterWgt.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <qregularexpression.h>
#include <QTimer>
#include <Common/PublicFun.h>
#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"
#include "Common/HttpMgr.h"

WRegisterWgt::WRegisterWgt(QWidget* parent):
	WLoadUIWgtBase(WgtFile::RegDlgPath,parent)
{
	InitHttpHandlers();
}

WRegisterWgt::~WRegisterWgt()
{
}

void WRegisterWgt::slotRegModFinish(const int ReqID, const QString& Res, const int ErrCode)
{
	QJsonObject jsonObj;
	if(!Tool::ParserResponJson(Res, jsonObj, ErrCode))
	{
		UIHelper::SetTipState(Lab_ErrTip, ErrorCodes::GetErrorStr(ErrCode), false);
	}

	//调用对应的逻辑
	if(Handlers.find(ReqID)== Handlers.end())
	{
		UIHelper::SetTipState(Lab_ErrTip, tr("注册收到返回，但未找到对应方法: %1").arg(ReqID), false);
		qDebug("注册请求的返回，未找到对应的执行方法！ID:%d", ReqID);
		return;
	}

	Handlers[ReqID](jsonObj);

}

void WRegisterWgt::InitControls()
{
	Btn_Ok = UI->findChild<QPushButton*>("Btn_Ok");
	Q_ASSERT(Btn_Ok != nullptr);

	Edt_Confirm = UI->findChild<QLineEdit*>("Edt_Confirm");
	Q_ASSERT(Edt_Confirm != nullptr);

	Edt_Password = UI->findChild<QLineEdit*>("Edt_Password");
	Q_ASSERT(Edt_Password != nullptr);

	Lab_ErrTip = UI->findChild<QLabel*>("Lab_ErrTip");
	Q_ASSERT(Lab_ErrTip != nullptr);

	Edt_Email = UI->findChild<QLineEdit*>("Edt_Email");
	Q_ASSERT(!Edt_Email);

	Edt_User = UI->findChild<QLineEdit*>("Edt_User");
	Q_ASSERT(!Edt_User);

	Edt_Verify = UI->findChild<QLineEdit*>("Edt_Verify");
	Q_ASSERT(!Edt_Verify);

	Btn_GetCode = UI->findChild<QPushButton*>("Btn_GetCode");
	Q_ASSERT(!Btn_GetCode);

	//设置密码显示格式隐藏
	Edt_Confirm->setEchoMode(QLineEdit::Password);
	Edt_Password->setEchoMode(QLineEdit::Password);

	Lab_ErrTip->setProperty("state", "normal");//设置属性状态，QSS存在指定
	Lab_ErrTip->clear();//保留布局又能隐藏
}

void WRegisterWgt::ConnectSigSlot()
{
	connect(UI->findChild<QPushButton*>("Btn_Cancel"),&QPushButton::clicked,this,[this]()
	{
		SetControlsToNormal();
		emit sigBtnCancelClicked();
	});
	connect(Btn_Ok, &QPushButton::clicked, this, &WRegisterWgt::slotRegister);

	//获取验证码
	connect(Btn_GetCode, &QPushButton::clicked, this, [this]()
	{
			SetControlsToNormal();
			
			//验证邮箱的地址正则表达式
			const auto& EmailStr = Edt_Email->text();

			if (IsAllEdtInputMatch()) {
				//发送http请求获取验证码
				QJsonObject json_obj;
				json_obj["email"] = EmailStr;
				SHttpMgr::GetInstance().PostHttpReq(QUrl(Net::RequestMain()+Net::URI_GET_VERIFICATION), json_obj, ReqID::ID_GET_VARIFY_CODE, Modules::REGISTERMOD);

				//验证码发送之后，相应控件进行禁用
				SetRegControlEnable(false);
				Btn_GetCode->setEnabled(false);
			}
	});

	connect(&SHttpMgr::GetInstance(), &SHttpMgr::sigRegModFinish, this, &WRegisterWgt::slotRegModFinish);

}

void WRegisterWgt::InitHttpHandlers()
{
	Handlers.emplace(ReqID::ID_GET_VARIFY_CODE, [this](const QJsonObject& JsonObj)
	{
		int Error = JsonObj["error"].toInt();
		if (Error != ErrorCodes::SUCCESS) {
			UIHelper::SetTipState(Lab_ErrTip,tr("参数错误"), false);

			//获取验证码失败，得重新启动一些控件
			SetRegControlEnable(true);
			Btn_GetCode->setEnabled(true);

			return;
		}
		auto Email = JsonObj["email"].toString();
		UIHelper::SetTipState(Lab_ErrTip,tr("验证码已发送到邮箱，注意查收"), true);
		SetRegControlEnable(false);
		qDebug() << "email is " << Email;
	});

	Handlers.emplace(ReqID::ID_REG_USER, [this](const QJsonObject& JsonObj)
	{
		int error = JsonObj["error"].toInt();
		if (error != ErrorCodes::SUCCESS)
		{
			auto ErrorStr = ErrorCodes::GetErrorStr(error);
			UIHelper::SetTipState(Lab_ErrTip,ErrorStr, false);
			SetRegControlEnable(true);
			Btn_GetCode->setEnabled(true);
			return;
		}
		auto email = JsonObj["email"].toString();
		UIHelper::SetTipState(Lab_ErrTip,tr("注册成功! 即将返回登陆界面"), true);

		QTimer::singleShot(1000, this, [this]()
			{
				emit sigBtnCancelClicked();
				SetControlsToNormal();
			});

		qDebug() << "email is " << email;
	});
}

void WRegisterWgt::SetControlsToNormal()
{
	Lab_ErrTip->setText("");

	SetRegControlEnable();

	UIHelper::SetLineEditError(Edt_Email);
	UIHelper::SetLineEditError(Edt_User);
	UIHelper::SetLineEditError(Edt_Password);
	UIHelper::SetLineEditError(Edt_Confirm);
	UIHelper::SetLineEditError(Edt_Verify);
	
}

bool WRegisterWgt::IsAllEdtInputMatch()
{
	if (!Tool::IsUserNameMatch(Edt_User->text()))
	{
		UIHelper::SetTipState(Lab_ErrTip,"请输入6位以上的用户名", false);
		UIHelper::SetLineEditError(Edt_User, true);
		return false;
	}

	if (Edt_Email->text().isEmpty() || !Tool::IsStrMatchEmail(Edt_Email->text()))
	{
		UIHelper::SetTipState(Lab_ErrTip,"邮箱格式不正确", false);
		UIHelper::SetLineEditError(Edt_Email, true);
		return false;
	}

	if (!Tool::IsPasswdMatch(Edt_Password->text()))
	{
		UIHelper::SetTipState(Lab_ErrTip,"请输入8位以上的密码，必须存在大小写字母", false);
		UIHelper::SetLineEditError(Edt_Password, true);
		return false;
	}
	if (Edt_Password->text() != Edt_Confirm->text())
	{
		UIHelper::SetTipState(Lab_ErrTip,"密码不配对", false);
		UIHelper::SetLineEditError(Edt_Confirm, true);
		return false;
	}

	Lab_ErrTip->clear();

	UIHelper::SetLineEditError(Edt_Email);
	UIHelper::SetLineEditError(Edt_User);
	UIHelper::SetLineEditError(Edt_Password);
	UIHelper::SetLineEditError(Edt_Confirm);
	UIHelper::SetLineEditError(Edt_Verify);

	return true;
}

void WRegisterWgt::SetRegControlEnable(const bool bEnable)
{
	if (Edt_User)Edt_User->setEnabled(bEnable);
	if (Edt_Email)Edt_Email->setEnabled(bEnable);
	if (Edt_Password)Edt_Password->setEnabled(bEnable);
	if (Edt_Confirm)Edt_Confirm->setEnabled(bEnable);
}

void WRegisterWgt::slotRegister()
{
	SetControlsToNormal();

	if(!IsAllEdtInputMatch()) return;
	
	if(Edt_Verify->text().length()<4)
	{
		UIHelper::SetTipState(Lab_ErrTip,"验证码格式错误", false);
		UIHelper::SetLineEditError(Edt_Verify, true);
		return;
	}

	//请求注册
	QJsonObject JsonObj;
	JsonObj["user"] = Edt_User->text();
	JsonObj["email"] = Edt_Email->text();
	JsonObj["passwd"] = Tool::EcryptionStr(Edt_Password->text());
	JsonObj["confirm"] = Tool::EcryptionStr(Edt_Confirm->text());
	JsonObj["varifycode"] = Edt_Verify->text();
	SHttpMgr::GetInstance().PostHttpReq(QUrl(Net::RequestMain() + Net::URI_USER_REGISTER),
		JsonObj, ReqID::ID_REG_USER, Modules::REGISTERMOD);
}


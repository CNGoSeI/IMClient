#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <qregularexpression.h>
#include <QJsonDocument>
#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"
#include "Common/HttpMgr.h"
#include "RegisterWgt.h"
#include <QJsonObject>
#include <Common/PublicFun.h>

WRegisterWgt::WRegisterWgt(QWidget* parent):
	WLoadUIWgtBase(WgtFile::RegDlgPath,parent)
{
	InitHttpHandlers();
}

WRegisterWgt::~WRegisterWgt()
{
}

void WRegisterWgt::ShowTip(const QString& Tip, bool b_ok)
{

	if (b_ok) {
		Lab_ErrTip->setProperty("state", "normal");
	}
	else {
		Lab_ErrTip->setProperty("state", "err");
	}

	Lab_ErrTip->setText(Tip);
	//设置状态之后更新QSS
	UIHelper::RePolish(Lab_ErrTip);
}

void WRegisterWgt::slotRegModFinish(const int ReqID, const QString& Res, const int ErrCode)
{
	if (ErrCode != ErrorCodes::SUCCESS) {
		ShowTip(tr("网络请求错误"), false);
		return;
	}

	// 解析 JSON 字符串,res需转化为QByteArray
	QJsonDocument jsonDoc = QJsonDocument::fromJson(Res.toUtf8());
	//json解析错误
	if (jsonDoc.isNull()) {
		ShowTip(tr("json解析错误"), false);
		return;
	}

	//json解析错误
	if (!jsonDoc.isObject()) {
		ShowTip(tr("json解析错误"), false);
		return;
	}

	QJsonObject jsonObj = jsonDoc.object();

	//调用对应的逻辑
	if(Handlers.find(ReqID)== Handlers.end())
	{
		ShowTip(tr("未找到相应处理方法 ID: %1").arg(ReqID),false);
		return;
	}
	Handlers[ReqID](jsonDoc.object());
	return;
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

	//设置密码显示格式隐藏
	Edt_Confirm->setEchoMode(QLineEdit::Password);
	Edt_Password->setEchoMode(QLineEdit::Password);

	Lab_ErrTip->setProperty("state", "normal");//设置属性状态，QSS存在指定
	UIHelper::RePolish(Lab_ErrTip);
	Lab_ErrTip->setText("");//保留布局又能隐藏
}

void WRegisterWgt::ConnectSigSlot()
{
	connect(UI->findChild<QPushButton*>("Btn_Cancel"),&QPushButton::clicked,this,[this]()
	{
		SetTotalControlToNormal();
		emit sigBtnCancelClicked();
	});
	connect(Btn_Ok, &QPushButton::clicked, this, &WRegisterWgt::slotRegister);

	//获取验证码 验证邮箱输入框是否合规
	connect(UI->findChild<QPushButton*>("Btn_GetCode"), &QPushButton::clicked, this, [this]()
	{
			SetTotalControlToNormal();
			
			//验证邮箱的地址正则表达式
			const auto& EmailStr = Edt_Email->text();
			// 邮箱地址的正则表达式

			if (IsAllEdtInputMatch()) {
				//发送http请求获取验证码
				QJsonObject json_obj;
				json_obj["email"] = EmailStr;
				SHttpMgr::GetInstance().PostHttpReq(QUrl(Net::RequestMain()+Net::URI_GET_VERIFICATION), json_obj, ReqID::ID_GET_VARIFY_CODE, Modules::REGISTERMOD);

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
			ShowTip(tr("参数错误"), false);
			return;
		}
		auto Email = JsonObj["email"].toString();
		ShowTip(tr("验证码已发送到邮箱，注意查收"), true);
		qDebug() << "email is " << Email;
	});

	Handlers.emplace(ReqID::ID_REG_USER, [this](const QJsonObject& JsonObj)
	{
		int error = JsonObj["error"].toInt();
		if (error != ErrorCodes::SUCCESS)
		{
			ShowTip(tr("参数错误"), false);
			return;
		}
		auto email = JsonObj["email"].toString();
		ShowTip(tr("注册成功"), true);
		qDebug() << "email is " << email;
	});
}

void WRegisterWgt::SetTotalControlToNormal()
{
	Lab_ErrTip->setText("");

	UIHelper::SetLineEditError(Edt_Email);
	UIHelper::SetLineEditError(Edt_User);
	UIHelper::SetLineEditError(Edt_Password);
	UIHelper::SetLineEditError(Edt_Confirm);
	UIHelper::SetLineEditError(Edt_Verify);
}

bool WRegisterWgt::IsAllEdtInputMatch()
{
	if (Edt_User->text().length() < 6)
	{
		ShowTip("请输入6位以上的用户名", false);
		UIHelper::SetLineEditError(Edt_User, true);
		return false;
	}

	if (Edt_Email->text().isEmpty() || !Tool::IsStrMatchEmail(Edt_Email->text()))
	{
		ShowTip("邮箱格式不正确", false);
		UIHelper::SetLineEditError(Edt_Email, true);
		return false;
	}

	if (Edt_Password->text().length() < 8)
	{
		ShowTip("请输入8位以上的密码", false);
		UIHelper::SetLineEditError(Edt_Password, true);
		return false;
	}
	if (Edt_Password->text() != Edt_Confirm->text())
	{
		ShowTip("密码不配对", false);
		UIHelper::SetLineEditError(Edt_Confirm, true);
		return false;
	}

	return true;
}

void WRegisterWgt::slotRegister()
{
	SetTotalControlToNormal();

	if(!IsAllEdtInputMatch()) return;
	
	if(Edt_Verify->text().length()<4)
	{
		ShowTip("验证码格式错误", false);
		UIHelper::SetLineEditError(Edt_Verify, true);
		return;
	}

	//请求注册
	QJsonObject JsonObj;
	JsonObj["user"] = Edt_User->text();
	JsonObj["email"] = Edt_Email->text();
	JsonObj["passwd"] = Edt_Password->text();
	JsonObj["confirm"] = Edt_Confirm->text();
	JsonObj["varifycode"] = Edt_Verify->text();
	SHttpMgr::GetInstance().PostHttpReq(QUrl(Net::RequestMain() + Net::URI__USER_REGISTER),
		JsonObj, ReqID::ID_REG_USER, Modules::REGISTERMOD);
}


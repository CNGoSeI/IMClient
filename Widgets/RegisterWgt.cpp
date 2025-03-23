#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <qregularexpression.h>
#include <QJsonDocument>
#include <QString>
#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"
#include "Common/HttpMgr.h"
#include "RegisterWgt.h"

#include <QJsonObject>

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

	//设置密码显示格式隐藏
	Edt_Confirm->setEchoMode(QLineEdit::Password);
	Edt_Password->setEchoMode(QLineEdit::Password);

	Lab_ErrTip->setProperty("state", "normal");//设置属性状态，QSS存在指定
	UIHelper::RePolish(Lab_ErrTip);
	Lab_ErrTip->setText("");//保留布局又能隐藏
}

void WRegisterWgt::ConnectSigSlot()
{
	connect(Btn_Ok,&QPushButton::clicked,this,&WRegisterWgt::sigBtnOkClicked);

	//获取验证码 验证邮箱输入框是否合规
	connect(UI->findChild<QPushButton*>("Btn_GetCode"), &QPushButton::clicked, this, [this]()
	{
			Lab_ErrTip->setText("");
			//验证邮箱的地址正则表达式
			auto EmailStr = UI->findChild<QLineEdit*>("Edt_Email")->text();
			// 邮箱地址的正则表达式
			QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
			bool match = regex.match(EmailStr).hasMatch(); // 执行正则表达式匹配
			if (match) {
				//发送http请求获取验证码
				QJsonObject json_obj;
				json_obj["email"] = EmailStr;
				SHttpMgr::GetInstance().PostHttpReq(QUrl(Net::RequestMain()+Net::URI_GET_VERIFICATION), json_obj, ReqID::ID_GET_VARIFY_CODE, Modules::REGISTERMOD);

			}
			else {
				//提示邮箱不正确
				this->ShowTip(tr("邮箱地址不正确"),false);
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
}

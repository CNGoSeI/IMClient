#include "RegisterWgt.h"
#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"
#include "Common/HttpMgr.h"
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <qregularexpression.h>

WRegisterWgt::WRegisterWgt(QWidget* parent):
	WLoadUIWgtBase(WgtFile::RegDlgPath,parent)
{
}

WRegisterWgt::~WRegisterWgt()
{
}

void WRegisterWgt::ShowErrTip(const QString& Tip)
{
	Lab_ErrTip->setText(Tip);
	//设置状态之后高兴QSS
	Lab_ErrTip->setProperty("state", "err");
	UIHelper::RePolish(Lab_ErrTip);
	Lab_ErrTip->setVisible(true);
}

void WRegisterWgt::slotRegModFinish(const int ReqID, const QString& Res, const int ErrCode)
{

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
			}
			else {
				//提示邮箱不正确
				this->ShowErrTip(tr("邮箱地址不正确"));
			}
	});

	connect(SHttpMgr::GetInstance(), &SHttpMgr::sigRegModFinish, this, &WRegisterWgt::slotRegModFinish);
}

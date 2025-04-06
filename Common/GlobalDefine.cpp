#include "GlobalDefine.h"
#include <QLineEdit>
#include <QSettings>
#include <QLabel>

const QSettings gSettings("./configs/config.ini", QSettings::IniFormat);
const QString gNoneErrorStr("未知错误");

void UIHelper::RePolish(QWidget* TargetWgt)
{
	//取消style状态之后再填入状态
	TargetWgt->style()->unpolish(TargetWgt);
	TargetWgt->style()->polish(TargetWgt);
}

void UIHelper::SetTipState(QLabel* TipWgt, const QString& Tip, const bool bOk)
{
	if (!TipWgt)return;

	if (bOk)
	{
		TipWgt->setProperty("state", "normal");
	}
	else
	{
		TipWgt->setProperty("state", "err");
	}

	TipWgt->setText(Tip);
	//设置状态之后更新QSS
	UIHelper::RePolish(TipWgt);
}

void UIHelper::SetLineEditError(QLineEdit* Target, bool IsError)
{
	if (!Target || !Target->isVisible())
	{
		return;
	}
	Target->setProperty("error", IsError);
	Target->style()->unpolish(Target);
	Target->style()->polish(Target);
}
;

const QString& Net::UrlHome()
{
	// 读取键值，第二个参数为默认值（若键不存在）
	static QString Host = gSettings.value("GateServer/host"/*, "localhost"*/).toString();

	return Host;
}

const QString& Net::NetPort()
{
	static QString Port = gSettings.value("GateServer/port"/*, "9527"*/).toString();

	return Port;
}

const QString& Net::RequestMain()
{
	static QString MainUrl = QString("%1%2:%3/").arg(UrlBegin).arg(Net::UrlHome()).arg(Net::NetPort());
	//Net::UrlBegin + "://" + Net::UrlHome() + ":" + Net::NetPort + "/";
	return MainUrl;
}

const QString& ErrorCodes::GetErrorStr(const int Code)
{
	static std::map<int, QString> ErroCode2Str = []()
	{
		std::map<int, QString> ErroCode2Str;
		ErroCode2Str.emplace(ERR_JSON, "参数解析出错");
		ErroCode2Str.emplace(ERR_NETWORK, "网络出错");
		ErroCode2Str.emplace(Send_Email_FAILD, "邮箱不存在，验证码发送失败");

		ErroCode2Str.emplace(VarifyExpired, "验证码无效");
		ErroCode2Str.emplace(UserExist, "用户或者邮箱已经存在");
		ErroCode2Str.emplace(VarifyCodeErr, "验证码错误");
		ErroCode2Str.emplace(EmailNotMatch, "邮箱或者用户名错误");
		ErroCode2Str.emplace(PasswdUpFailed, "重置密码失败");

		return std::move(ErroCode2Str);
	}();

	auto it = ErroCode2Str.find(Code);
	if (it != ErroCode2Str.end()) return it->second;
	return gNoneErrorStr;
}

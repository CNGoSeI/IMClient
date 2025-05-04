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

QColor UIHelper::GetTargetColor(const QString& ColorTag)
{
	QColor color;
	static QString root = "UI/";
	QString Tag = root+ ColorTag+"%1";
	color.setRed(gSettings.value(Tag.arg("R")).toInt());
	color.setGreen(gSettings.value(Tag.arg("G")).toInt());
	color.setBlue(gSettings.value(Tag.arg("B")).toInt());
	return color;
}

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
		ErroCode2Str.emplace(RPCFailed, "服务器间通信故障");
		ErroCode2Str.emplace(UserExist, "用户或者邮箱已经存在");
		ErroCode2Str.emplace(VarifyCodeErr, "验证码错误");
		ErroCode2Str.emplace(EmailNotMatch, "邮箱或者用户名错误");
		ErroCode2Str.emplace(PasswdUpFailed, "重置密码失败");
		ErroCode2Str.emplace(PasswdInvalid, "用户名或密码错误");
		ErroCode2Str.emplace(RPCGetFailed, "聊天服务器通信故障");
		return std::move(ErroCode2Str);
	}();

	auto it = ErroCode2Str.find(Code);
	if (it != ErroCode2Str.end()) return it->second;
	return gNoneErrorStr;
}

Infos::BaseUserInfo::BaseUserInfo(const int InUID, const QString& InName, const QString& InIconPath):
	HeadIconPath(InIconPath),
	Name(InName),
	UID(InUID)
{

}

Infos::BaseUserInfo::BaseUserInfo(const FAddFriendApply& AddFriendApply):
	HeadIconPath(AddFriendApply.Icon),
	Name(AddFriendApply.Name),
	UID(AddFriendApply.FromUid)
{

}

Infos::BaseUserInfo& Infos::BaseUserInfo::operator=(const BaseUserInfo& other)
{
	if (this != &other) // 防止自赋值
	{
		UID = other.UID; // QString深拷贝安全
		Name = other.Name;
		HeadIconPath = other.HeadIconPath;
		Sex = other.Sex; // bool直接赋值
		Desc = other.Desc;
	}
	return *this; // 返回左值引用
}

Infos::FSearchInfo::FSearchInfo(int uid, QString name, QString nick, QString desc, int sex):
	UID(uid),
	Name(name),
	Desc(desc),
	Sex(sex)
{
}

Infos::FAddFriendApply::FAddFriendApply(int from_uid, const QString& name, const QString& desc, const QString& icon, const QString& nick, int sex):
	FromUid(from_uid),
	Name(name),
	Desc(desc),
	Icon(icon),
	Nick(nick),
	Sex(sex)
{
}

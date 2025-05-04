#include "ReqApplyFriend.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QLineEdit>
#include <QPushButton>

#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"
#include "Common/TcpMgr.h"
#include "Common/UserMgr.h"

WReqApplyFriend::WReqApplyFriend(QWidget* parent):
	ILoadUIWgtBase(WgtFile::AddFriendWgt,parent)
{
	UI->setWindowFlags(UI->windowFlags()/* | Qt::FramelessWindowHint*/ | Qt::Window);
	UI->setAttribute(Qt::WA_TranslucentBackground);//透明背景
}

void WReqApplyFriend::SetSearchInfo(const Infos::FSearchInfo& InInfo)
{
	Si = InInfo;
	QString applyname = SUserMgr::GetInstance().GetName();

	Edt_Name->setText(Si.Name);
	Edt_BackName->setText(Si.Name);
}

void WReqApplyFriend::InitControls()
{
	Edt_AddLab = UIHelper::AssertFindChild<QLineEdit*>(UI, "Edt_AddLab");
	Edt_BackName = UIHelper::AssertFindChild<QLineEdit*>(UI, "Edt_BackName");
	Edt_Name = UIHelper::AssertFindChild<QLineEdit*>(UI, "Edt_Name");
	Btn_Cancel= UIHelper::AssertFindChild<QPushButton*>(UI, "Btn_Cancel");
	Btn_OK = UIHelper::AssertFindChild<QPushButton*>(UI, "Btn_OK");
}

void WReqApplyFriend::ConnectSigSlot()
{
	connect(Btn_OK, &QPushButton::clicked, [this]()
	{
		ApplySure();
		UI->close();
		this->deleteLater();
	});

	connect(Btn_Cancel, &QPushButton::clicked, [this]()
	{
		UI->close();
		this->deleteLater();
	});
}

void WReqApplyFriend::ApplySure() const
{

	QJsonObject jsonObj;
	auto uid = SUserMgr::GetInstance().GetUid();
	jsonObj["uid"] = uid;
	auto name = Edt_Name->text();
	if (name.isEmpty()) {
		name = Edt_Name->placeholderText();
	}

	jsonObj["applyname"] = name;
	auto bakname = Edt_BackName->text();
	if (bakname.isEmpty()) {
		bakname = Edt_BackName->placeholderText();
	}
	jsonObj["bakname"] = bakname;
	jsonObj["touid"] = Si.UID;

	QJsonDocument doc(jsonObj);
	QByteArray jsonData = doc.toJson(QJsonDocument::Compact);

	//发送tcp请求给chat server
	emit STcpMgr::GetInstance().sigSendData(ReqID::ID_ADD_FRIEND_REQ, jsonData);
}

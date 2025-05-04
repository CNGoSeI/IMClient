#include "ApplyFriendLstItem.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QPushButton>

#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"
#include "Common/TcpMgr.h"
#include "Common/UserMgr.h"

WApplyFriendLstItem::WApplyFriendLstItem(QWidget* parent) :
	IUserInfoLstItem(WgtFile::ApplyFriendLstItem, EListItemType::APPLY_FRIEND_ITEM, parent)
{

}

void WApplyFriendLstItem::SetInfo(std::unique_ptr<Infos::BaseUserInfo> InInfo)
{
	if (!Info) Info = std::make_unique<Infos::BaseUserInfo>();
	Lab_AddName->setText(InInfo->Name);
	Lab_AddMsg->setText(InInfo->Desc);//当作添加时候的招呼语吧

	QPixmap Icon(InInfo->HeadIconPath);
	Lab_Icon->setPixmap(Icon.scaled(Lab_Icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	Lab_Icon->setScaledContents(true);

	Info = std::move(InInfo);
}

void WApplyFriendLstItem::InitControls()
{
	Btn_AddState = UIHelper::AssertFindChild<QPushButton*>(UI, "Btn_AddState");
	Lab_AddMsg= UIHelper::AssertFindChild<QLabel*>(UI, "Lab_AddMsg");
	Lab_AddName = UIHelper::AssertFindChild<QLabel*>(UI, "Lab_AddName");
	Lab_Icon = UIHelper::AssertFindChild<QLabel*>(UI, "Lab_Icon");
	Btn_AddState->setEnabled(true);
}

void WApplyFriendLstItem::ConnectSigSlot()
{
	connect(Btn_AddState, &QPushButton::clicked, this, [this]()
	{
		//添加发送逻辑
		QJsonObject jsonObj;
		auto uid = SUserMgr::GetInstance().GetUid();
		jsonObj["fromuid"] = uid;
		jsonObj["touid"] = Info->UID;

		jsonObj["back"] = Info->Name;

		QJsonDocument doc(jsonObj);
		QByteArray jsonData = doc.toJson(QJsonDocument::Compact);

		//发送tcp请求给chat server
		emit STcpMgr::GetInstance().sigSendData(ReqID::ID_AUTH_FRIEND_REQ, jsonData);
		Btn_AddState->setText(tr("已同意"));
		Btn_AddState->setEnabled(false);
	});
}

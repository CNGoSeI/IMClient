#include "ConUserItem.h"

#include <QLabel>

#include "MainChatWgt.h"
#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"

WConUserItem::WConUserItem(QWidget* parent):
	IUserInfoLstItem(WgtFile::ContactUserItem,EListItemType::CONTACT_USER_ITEM,parent)
{
}

void WConUserItem::SetInfo(std::unique_ptr<Infos::BaseUserInfo> InInfo)
{
	Lab_BigName->setText(InInfo->Name);
	Lab_UserSlogen->setText(InInfo->Desc);//t填写时以此为slogen

	QPixmap Icon(InInfo->HeadIconPath);
	Lab_Icon->setPixmap(Icon.scaled(Lab_Icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	Lab_Icon->setScaledContents(true);

	Info = std::move(InInfo);
}

void WConUserItem::InitControls()
{
	Lab_BigName = UIHelper::AssertFindChild<QLabel*>(UI, "Lab_BigName");
	Lab_UserSlogen = UIHelper::AssertFindChild<QLabel*>(UI, "Lab_UserSlogen");
	Lab_Icon = UIHelper::AssertFindChild<QLabel*>(UI, "Lab_Icon");
}

void WConUserItem::ConnectSigSlot()
{
	
}

WConUserItem::~WConUserItem()
{
}

void WConUserItem::BeDoubelClicked(QListWidgetItem* item)
{
	WChatWgt::GetIns().SwitchToChatPage(*Info);
}

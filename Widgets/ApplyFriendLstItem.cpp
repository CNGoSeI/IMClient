#include "ApplyFriendLstItem.h"

#include <QLabel>
#include <QPushButton>

#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"

WApplyFriendLstItem::WApplyFriendLstItem(QWidget* parent) :
	IUserInfoLstItem(WgtFile::ApplyFriendLstItem, EListItemType::APPLY_FRIEND_ITEM, parent)
{

}

void WApplyFriendLstItem::SetInfo(std::unique_ptr<Infos::BaseUserInfo> InInfo)
{
	Lab_AddName->setText(InInfo->Name);
	Lab_AddMsg->setText(InInfo->Desc);//当作添加时候的招呼语吧

	QPixmap Icon(InInfo->HeadIconPath);
	Lab_Icon->setPixmap(Icon.scaled(Lab_Icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	Lab_Icon->setScaledContents(true);
	Btn_AddState->setVisible(true);
}

void WApplyFriendLstItem::InitControls()
{
	Btn_AddState = UIHelper::AssertFindChild<QPushButton*>(UI, "Btn_AddState");
	Lab_AddMsg= UIHelper::AssertFindChild<QLabel*>(UI, "Lab_AddMsg");
	Lab_AddName = UIHelper::AssertFindChild<QLabel*>(UI, "Lab_AddName");
	Lab_Icon = UIHelper::AssertFindChild<QLabel*>(UI, "Lab_Icon");
}

void WApplyFriendLstItem::ConnectSigSlot()
{
	
}

#include "ApplyFriendLstItem.h"

#include <QLabel>
#include <QPushButton>

#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"

WApplyFriendLstItem::WApplyFriendLstItem(QWidget* parent) :
	IListItemWgt(WgtFile::ApplyFriendLstItem, EListItemType::APPLY_FRIEND_ITEM, parent)
{

}

void WApplyFriendLstItem::SetInfoImpl(const QString& Name, const QString& Message, const QString& IconPath)
{
	Lab_AddName->setText(Name);
	Lab_AddMsg->setText(Message);

	QPixmap Icon(IconPath);
	Lab_Icon->setPixmap(Icon.scaled(Lab_Icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	Lab_Icon->setScaledContents(true);
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

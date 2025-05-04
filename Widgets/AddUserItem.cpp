#include "AddUserItem.h"

#include "MainChatWgt.h"
#include "WidgetFilesHelper.h"

CAddUserItem::CAddUserItem(QWidget* parent):
	IUserInfoLstItem(WgtFile::AddUserItem, EListItemType::ADD_USER_TIP_ITEM, parent)
{

}

void CAddUserItem::SetInfo(std::unique_ptr<Infos::BaseUserInfo>)
{
}

void CAddUserItem::InitControls()
{
}

void CAddUserItem::BeClicked(QListWidgetItem* item)
{
	emit sigBeClicked();
}

void CAddUserItem::ConnectSigSlot()
{
	connect(this, &CAddUserItem::sigBeClicked, &WChatWgt::GetIns(), &WChatWgt::slotTryFindUser);
}

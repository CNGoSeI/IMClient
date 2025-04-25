#include "AddUserItem.h"
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

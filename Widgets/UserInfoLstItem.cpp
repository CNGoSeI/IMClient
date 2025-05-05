#include "UserInfoLstItem.h"

IUserInfoLstItem::IUserInfoLstItem(const QString& UIRes, EListItemType InItemType, QWidget* parent):
	IListItemWgt(UIRes, InItemType,parent)
{
	Info = std::make_unique<Infos::BaseUserInfo>();
}

IUserInfoLstItem::~IUserInfoLstItem()
{

}

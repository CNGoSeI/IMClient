#include "UserInfoLstItem.h"

IUserInfoLstItem::IUserInfoLstItem(const QString& UIRes, EListItemType InItemType, QWidget* parent):
	IListItemWgt(UIRes, InItemType,parent)
{
}

IUserInfoLstItem::~IUserInfoLstItem()
{

}

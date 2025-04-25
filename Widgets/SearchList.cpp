#include "SearchList.h"

#include <QListWidget>

#include "AddUserItem.h"
#include "Common/TcpMgr.h"

CSearchList::CSearchList(QWidget* parent):
	ICustomList(parent)
{
}

void CSearchList::CloseFindDlg()
{
}

void CSearchList::AfterSetListFunc()
{

	//连接搜索条目
	//connect(&STcpMgr::GetInstance(), &STcpMgr::sigSearch, this, &CSearchList::slot_user_search);

    AddInfoItem(nullptr);
}

void CSearchList::SetSearchEdit(QWidget* edit)
{
}


IUserInfoLstItem* CSearchList::MakeNewUserItem()
{
    return new CAddUserItem(ListWgt);
}

void CSearchList::slotItemClicked(QListWidgetItem* item)
{
}

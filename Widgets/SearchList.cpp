#include "SearchList.h"

#include <QListWidget>

#include "AddUserItem.h"
#include "LoadingWgt.h"
#include "MainChatWgt.h"
#include "ReqApplyFriend.h"
#include "Common/GlobalDefine.h"
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
	FriendApplayWgt = new WReqApplyFriend(ListWgt->parentWidget());
	FriendApplayWgt->CreateWgt();
	//连接搜索条目
	connect(&STcpMgr::GetInstance(), &STcpMgr::sigUserSearch, this, &CSearchList::slotUserSearch);

    AddInfoItem(nullptr);
}

void CSearchList::SetSearchEdit(QWidget* edit)
{
}


IUserInfoLstItem* CSearchList::MakeNewUserItem()
{
    return new CAddUserItem(ListWgt);
}

void CSearchList::slotUserSearch(const Infos::FSearchInfo& Info)
{

	//此处分两种情况，一种是搜多到已经是自己的朋友了，一种是未添加好友
	//查找是否已经是好友 todo...
	FriendApplayWgt->SetSearchInfo(Info);
	FriendApplayWgt->GetUI()->show();
}

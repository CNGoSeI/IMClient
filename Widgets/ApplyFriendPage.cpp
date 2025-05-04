#include "ApplyFriendPage.h"

#include <QListWidget>

#include "ListApplyFriend.h"
#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"
#include "Common/RedDotNode.h"

WApplyFriendPage::WApplyFriendPage(QWidget* parent):
	ILoadUIWgtBase(WgtFile::ApplyFriendWgt,parent)
{
}

void WApplyFriendPage::slotAddFriendReqItem(const Infos::FAddFriendApply& Info)
{
	//auto UserInfo = s;
	ApplyFriendLstMgr->AddInfoItem(std::make_unique<Infos::BaseUserInfo>(Info));
	SRedDotMgr::Ins().NotifyTargetShow(true, RedNodeName::NewFriendReq.toStdString());
}

void WApplyFriendPage::InitControls()
{
	ApplyFriendLstMgr = std::make_unique<CListApplyFriend>();
	List_ApplyFriend = UIHelper::AssertFindChild<QListWidget*>(GetUI(), "List_ApplyFriend");
	ApplyFriendLstMgr->SetListWgt(List_ApplyFriend);
}

void WApplyFriendPage::ConnectSigSlot()
{
	ILoadUIWgtBase::ConnectSigSlot();
}

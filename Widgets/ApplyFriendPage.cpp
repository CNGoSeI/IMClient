#include "ApplyFriendPage.h"

#include <QListWidget>

#include "ApplyFriendLstItem.h"
#include "ConUserItem.h"
#include "ListApplyFriend.h"
#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"
#include "Common/RedDotNode.h"

WApplyFriendPage::WApplyFriendPage(QWidget* parent):
	ILoadUIWgtBase(WgtFile::ApplyFriendWgt,parent)
{
}

void WApplyFriendPage::slotAddFriendReqItem(const Infos::FAddFriendApply& Info,bool bNeedShowReddot)
{
	//auto UserInfo = s;
	auto item=ApplyFriendLstMgr->AddInfoItem(std::make_unique<Infos::BaseUserInfo>(Info));
	if(bNeedShowReddot)SRedDotMgr::Ins().NotifyTargetShow(true, RedNodeName::NewFriendReq.toStdString());
	if(bNeedShowReddot)return;

	if(auto AddFriendApplayItem= qobject_cast<WApplyFriendLstItem*>(item))
	{
		AddFriendApplayItem->SetAgreedAlready();
	}
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

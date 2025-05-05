#ifndef WGT_APPLYFRIENDPAGE_H
#define WGT_APPLYFRIENDPAGE_H
#include "Common/LoadUIWgtBase.h"

namespace Infos
{
	struct FAddFriendApply;
}

class CListApplyFriend;
class QListWidget;

class WApplyFriendPage:public ILoadUIWgtBase
{
	Q_OBJECT
public:
	WApplyFriendPage(QWidget* parent);

public slots:
	void slotAddFriendReqItem(const Infos::FAddFriendApply& Info,bool bNeedShowReddot);//添加一个好友请求item
protected:
	void InitControls() override;
	void ConnectSigSlot() override;

private:
	std::unique_ptr<CListApplyFriend> ApplyFriendLstMgr{nullptr};
	QListWidget* List_ApplyFriend{ nullptr };
};
#endif // WGT_APPLYFRIENDPAGE_H

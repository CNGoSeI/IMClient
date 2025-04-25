#ifndef WGT_APPLYFRIENDPAGE_H
#define WGT_APPLYFRIENDPAGE_H
#include "Common/LoadUIWgtBase.h"

class CListApplyFriend;
class QListWidget;

class WApplyFriendPage:public ILoadUIWgtBase
{
	Q_OBJECT
public:
	WApplyFriendPage(QWidget* parent);
protected:
	void InitControls() override;
	void ConnectSigSlot() override;

private:
	std::unique_ptr<CListApplyFriend> ApplyFriendLstMgr{nullptr};
	QListWidget* List_ApplyFriend{ nullptr };
};
#endif // WGT_APPLYFRIENDPAGE_H

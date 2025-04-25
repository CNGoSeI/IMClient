#ifndef WGT_APPLYFRIENDLSTITEM_H
#define WGT_APPLYFRIENDLSTITEM_H

/* 添加好友同意界面的Item */

#include "UserInfoLstItem.h"

class QLabel;
class QPushButton;

class WApplyFriendLstItem:public IUserInfoLstItem
{
	Q_OBJECT
public:
	WApplyFriendLstItem(QWidget* parent);
	void SetInfo(std::unique_ptr<Infos::BaseUserInfo> InInfo) override;
protected:
	void InitControls() override;
	void ConnectSigSlot() override;

private:
	QLabel* Lab_Icon{ nullptr };
	QLabel* Lab_AddName{ nullptr };
	QLabel* Lab_AddMsg{ nullptr }; //添加好友时候的申请用语
	QPushButton* Btn_AddState{ nullptr };
};
#endif // WGT_APPLYFRIENDLSTITEM_H

#ifndef WGT_APPLYFRIENDLSTITEM_H
#define WGT_APPLYFRIENDLSTITEM_H

/* 添加好友同意界面的Item */
#include "ListItemWgt.h"

class QLabel;
class QPushButton;

class WApplyFriendLstItem:public IListItemWgt
{
	Q_OBJECT
public:
	WApplyFriendLstItem(QWidget* parent);
	void SetInfoImpl(const QString& Name, const QString& Message, const QString& IconPath);
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

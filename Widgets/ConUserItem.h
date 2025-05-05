#ifndef WGT_CONUSERITEM_H
#define WGT_CONUSERITEM_H
/* 联系人列表的Item */
#include "UserInfoLstItem.h"

class QLabel;

class WConUserItem: public IUserInfoLstItem
{
	Q_OBJECT
public:
	WConUserItem(QWidget* parent);
	void SetInfo(std::unique_ptr<Infos::BaseUserInfo>) override;

protected:
	void InitControls() override;
	void ConnectSigSlot() override;

public:
	~WConUserItem() override;
	void BeDoubelClicked(QListWidgetItem* item) override;

private:
	QLabel* Lab_BigName{nullptr};
	QLabel* Lab_UserSlogen{ nullptr };//宣言
	QLabel* Lab_Icon{ nullptr };
};
#endif // WGT_CONUSERITEM_H

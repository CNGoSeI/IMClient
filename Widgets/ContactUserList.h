#ifndef CONTROL_CONTACTUSERLIST_H
#define CONTROL_CONTACTUSERLIST_H

#include "CustomList.h"

class CContactUserList:public ICustomList
{
	Q_OBJECT
public:
	CContactUserList(QWidget* parent = nullptr);

protected:
	void AfterSetListFunc() override;
	void SelfAddItems() override;
	void LoadingItems() override;
	void AppendWheelEvent(QWheelEvent* event, int, int) override;
	IUserInfoLstItem* MakeNewUserItem() override;
};
#endif // CONTROL_CONTACTUSERLIST_H

#ifndef CONTROL_LISTAPPLYFRIEND_H
#define CONTROL_LISTAPPLYFRIEND_H

#include "CustomList.h"

class CListApplyFriend:public ICustomList
{
	Q_OBJECT

public:
	CListApplyFriend(QWidget* parent = nullptr);

protected:
	void AppendWheelEvent(QWheelEvent* event, int, int) override;
	void AfterSetListFunc() override;
	void SelfAddItems() override;
	IUserInfoLstItem* MakeNewUserItem() override;

private:
	
};
#endif // CONTROL_LISTAPPLYFRIEND_H

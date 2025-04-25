#ifndef CONTROL_ADDUSERITEM_H
#define CONTROL_ADDUSERITEM_H

#include "UserInfoLstItem.h"

class CAddUserItem: public IUserInfoLstItem
{
	Q_OBJECT
public:
	CAddUserItem(QWidget* parent = nullptr);
	void SetInfo(std::unique_ptr<Infos::BaseUserInfo> ) override;
protected:
	void InitControls() override;
};
#endif // control_ADDUSERITEM_H

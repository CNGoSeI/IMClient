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

public:
	void BeClicked(QListWidgetItem* item) override;
signals:
	void sigBeClicked();

protected:
	void ConnectSigSlot() override;
};
#endif // control_ADDUSERITEM_H

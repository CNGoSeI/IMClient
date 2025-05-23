﻿#ifndef CONTROL_CHATUSERLIST_H
#define CONTROL_CHATUSERLIST_H
/*
 * 聊天界面联系人列表
 */
#include <QObject>

#include "CustomList.h"

class QListWidget;

class CChatUserList : public ICustomList
{
	Q_OBJECT

public:
	CChatUserList(QWidget* parent = nullptr);

protected:
	IUserInfoLstItem* MakeNewUserItem() override;
	void AppendWheelEvent(QWheelEvent* ,int ,int) override;
	void slotAdd();
	void SelfAddItems() override;
	void AfterSetListFunc() override;
	void LoadingItems() override;

};
#endif // CHATUSERLIST_H

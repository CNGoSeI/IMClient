#ifndef CONTROL_CHATUSERLIST_H
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
	void AppendWheelEvent(QWheelEvent* ,int ,int) override;
};
#endif // CHATUSERLIST_H

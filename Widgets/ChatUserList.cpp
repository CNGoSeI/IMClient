#include "ChatUserList.h"

#include <QWheelEvent>
#include <QListWidget>

CChatUserList::CChatUserList(QWidget* parent):
	ICustomList(parent)
{

}

void CChatUserList::AppendWheelEvent(QWheelEvent* event, int maxScrollValue, int currentValue)
{
	//int pageSize = 10; // 每页加载的联系人数量

	if (maxScrollValue - currentValue <= 0)
	{
		// 滚动到底部，加载新的联系人
		qDebug("界面到底，加载更多联系人");
		//发送信号通知聊天界面加载更多聊天内容
		emit sigLoadingItems();
	}
}

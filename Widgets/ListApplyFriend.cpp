#include "ListApplyFriend.h"

#include <QListWidgetItem>

#include "ApplyFriendLstItem.h"

CListApplyFriend::CListApplyFriend(QWidget* parent):
	ICustomList(parent)
{
}

void CListApplyFriend::AppendWheelEvent(QWheelEvent* event, int maxScrollValue, int currentValue)
{
    if (maxScrollValue - currentValue <= 0)
    {
        // 滚动到底部，加载新的联系人
        qDebug("界面到底，加载更多添加信息");
        //发送信号通知聊天界面加载更多聊天内容
       // emit sigLoadingItems();
    }
}

void CListApplyFriend::AfterSetListFunc()
{
	
}

void CListApplyFriend::SelfAddItems()
{

}

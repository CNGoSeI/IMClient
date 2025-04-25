#include "ListApplyFriend.h"

#include <QListWidgetItem>
#include <QRandomGenerator>

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
        LoadingItems();
    }
}

void CListApplyFriend::AfterSetListFunc()
{
	SelfAddItems();
}

void CListApplyFriend::SelfAddItems()
{
	for (int i = 0; i < 13; i++)
	{
		int randomValue = QRandomGenerator::global()->bounded(100); // 生成0到99之间的随机整数
		int str_i = randomValue % Test::Messages.size();
		int head_i = randomValue % Test::HeadIcons.size();
		int name_i = randomValue % Test::Names.size();

		auto Info = std::make_unique<Infos::BaseUserInfo>("", Test::Names[name_i], Test::HeadIcons[head_i]);
		Info->Desc = Test::Messages[str_i];
		auto Item = AddInfoItem(std::move(Info));

	}
}

IUserInfoLstItem* CListApplyFriend::MakeNewUserItem()
{
    return new WApplyFriendLstItem(ListWgt);
}

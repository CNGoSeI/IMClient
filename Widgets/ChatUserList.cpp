#include "ChatUserList.h"

#include <QWheelEvent>
#include <QListWidget>
#include <QRandomGenerator>

#include "ChatUserWid.h"
#include "LoadingWgt.h"
#include "MainChatWgt.h"
#include "Common/GlobalDefine.h"

CChatUserList::CChatUserList(QWidget* parent):
	ICustomList(parent)
{
	
}

IUserInfoLstItem* CChatUserList::MakeNewUserItem()
{
	return new WChatUserWid(ListWgt);
}

void CChatUserList::AppendWheelEvent(QWheelEvent* event, int maxScrollValue, int currentValue)
{
	//int pageSize = 10; // 每页加载的联系人数量

	if (maxScrollValue - currentValue <= 0)
	{
		// 滚动到底部，加载新的联系人
		qDebug("界面到底，加载更多联系人");
		//发送信号通知聊天界面加载更多聊天内容
		LoadingItems();
	}
}

void CChatUserList::slotAdd()
{
	
	if (bLoading) {
		return;
	}
	bLoading = true;
	SLoadingWgt::Instance().PopShow(WChatWgt::GetIns().GetUI());
	SelfAddItems();

	SLoadingWgt::Instance().HideStop();
	bLoading = false;
}

void CChatUserList::SelfAddItems()
{
	//TODO::最大加载数量了不再加载
	for (int i = 0; i < 13; i++)
	{
		int randomValue = QRandomGenerator::global()->bounded(100); // 生成0到99之间的随机整数
		int str_i = randomValue % Test::Messages.size();
		int head_i = randomValue % Test::HeadIcons.size();
		int name_i = randomValue % Test::Names.size();

		auto Item=AddInfoItem(std::make_unique<Infos::BaseUserInfo>(0, Test::Names[name_i], Test::HeadIcons[head_i]));
		if(auto ChatUserItem = qobject_cast<WChatUserWid*>(Item))
		{
			ChatUserItem->SetMessage(Test::Messages[str_i]);
		}

	}
}

void CChatUserList::AfterSetListFunc()
{
	slotAdd();
}

void CChatUserList::LoadingItems()
{
	slotAdd();
}

#include "ContactUserList.h"

#include <QListWidgetItem>
#include <QRandomGenerator>

#include "ConUserItem.h"
#include "Common/GlobalDefine.h"

CContactUserList::CContactUserList(QWidget* parent):
    ICustomList(parent)
{
}

void CContactUserList::AppendWheelEvent(QWheelEvent* event, int maxScrollValue, int currentValue)
{
    if (maxScrollValue - currentValue <= 0)
    {
        // 滚动到底部，加载新的联系人
        qDebug("界面到底，加载更多联系人");
        //发送信号通知聊天界面加载更多聊天内容
        emit sigLoadingItems();
    }
}

void CContactUserList::AfterSetListFunc()
{
    SelfAddItems();
    connect(this, &CContactUserList::sigLoadingItems, this, &CContactUserList::SelfAddItems);
}

void CContactUserList::SelfAddItems()
{
    // 创建QListWidgetItem，并设置自定义的widget
    for (int i = 0; i < 13; i++) {
        int randomValue = QRandomGenerator::global()->bounded(100); // 生成0到99之间的随机整数
        int str_i = randomValue % Test::Messages.size();
        int head_i = randomValue % Test::HeadIcons.size();
        int name_i = randomValue % Test::Names.size();

        //AddItemWithInfo(Test::Names[name_i], Test::Messages[str_i], Test::HeadIcons[head_i]);
    }
}

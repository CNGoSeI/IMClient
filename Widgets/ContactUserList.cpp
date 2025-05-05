#include "ContactUserList.h"

#include <QListWidgetItem>
#include <QRandomGenerator>

#include "ConUserItem.h"
#include "Common/GlobalDefine.h"
#include "Common/TcpMgr.h"
#include "Common/UserMgr.h"

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
        LoadingItems();
    }
}

IUserInfoLstItem* CContactUserList::MakeNewUserItem()
{
    return new WConUserItem(ListWgt);
}

void CContactUserList::AfterSetListFunc()
{
    SelfAddItems();

    connect(&STcpMgr::GetInstance(), &STcpMgr::sigAddAuthFriend, [this](const Infos::BaseUserInfo& baseinfo)
        {
            //判断如果已经是好友则跳过
            auto bfriend = SUserMgr::GetInstance().CheckFriendById(baseinfo.UID);
            if (bfriend) {
                return;
            }

            auto Item = AddInfoItem(std::make_unique<Infos::BaseUserInfo>(baseinfo.UID, baseinfo.Name, baseinfo.HeadIconPath));
            UId2Item.emplace(baseinfo.UID, Item);
        });
}

void CContactUserList::SelfAddItems()
{
    // 创建QListWidgetItem，并设置自定义的widget
    /*for (int i = 0; i < 13; i++) {
        int randomValue = QRandomGenerator::global()->bounded(100); // 生成0到99之间的随机整数
        int str_i = randomValue % Test::Messages.size();
        int head_i = randomValue % Test::HeadIcons.size();
        int name_i = randomValue % Test::Names.size();

        auto info = std::make_unique<Infos::BaseUserInfo>(0, Test::Names[name_i], Test::HeadIcons[head_i]);
        info->Desc = Test::Messages[str_i];//当作slogen吧
        AddInfoItem(std::move(info));
    }*/

}

void CContactUserList::LoadingItems()
{
    SelfAddItems();
}

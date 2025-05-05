#include "UserMgr.h"

#include <QJsonArray>

#include "Widgets/MainChatWgt.h"

void SUserMgr::SetName(const QString& name)
{
	Name = name;
}

void SUserMgr::SetUid(int uid)
{
	UId = uid;
}

void SUserMgr::SetToken(const QString& token)
{
	Token = token;
}

void SUserMgr::AppendApplyList(const QJsonArray& array)
{
    for (const QJsonValue& value : array) {
        auto name = value["name"].toString();
        auto desc = value["desc"].toString();
        auto icon = value["icon"].toString();
        auto nick = value["nick"].toString();
        auto sex = value["sex"].toInt();
        auto uid = value["uid"].toInt();
        auto status = value["status"].toInt();
        WChatWgt::GetIns().AddApplayFriendItem(Infos::FAddFriendApply(uid, name, desc, icon, nick, sex), status<1);
    }
}

void SUserMgr::AppendFriendList(const QJsonArray& array)
{
    // 遍历 QJsonArray 并输出每个元素
    for (const QJsonValue& value : array) {
        auto name = value["name"].toString();
        auto desc = value["desc"].toString();
        auto icon = value["icon"].toString();
        auto nick = value["nick"].toString();
        auto sex = value["sex"].toInt();
        auto uid = value["uid"].toInt();
        auto back = value["back"].toString();

        Infos::BaseUserInfo info(uid, name,icon);
        info.Sex = sex;
        info.Desc = desc;

        FriendMap.emplace(uid, info);
        WChatWgt::GetIns().AddConFriendItem(info);
    }
}

bool SUserMgr::CheckFriendById(int uid)
{
    auto iter = FriendMap.find(uid);
    if (iter == FriendMap.end()) {
        return false;
    }

    return true;
}

void SUserMgr::AddFriend(const Infos::BaseUserInfo& auth_rsp)
{
    FriendMap.emplace(auth_rsp.UID, auth_rsp);
}


const Infos::BaseUserInfo* SUserMgr::GetFriendById(int uid)
{
    auto find_it = FriendMap.find(uid);
    if (find_it == FriendMap.end()) {
        return nullptr;
    }

    return &find_it->second;
}

#ifndef USERMGR_H
#define USERMGR_H

#include <QObject>

#include "SingletonTemplate.h"

namespace Infos
{
	struct BaseUserInfo;
}

class SUserMgr:public QObject,public TSingleton<SUserMgr>
{
    Q_OBJECT
public:
    friend class TSingleton<SUserMgr>;
    ~SUserMgr()=default;
    void SetName(const QString& name);
    void SetUid(int uid);
    void SetToken(const QString& token);
    void SetIcon(const QString& icon) { Icon = icon; };

    const QString& GetName() const { return Name; };
    int GetUid() const { return UId; };
    const QString& GetToken() const { return Token; };
    const QString& GetIcon() const { return Icon; };
    void AppendApplyList(const QJsonArray& array);
    void AppendFriendList(const QJsonArray& array);
    bool CheckFriendById(int uid);
    void AddFriend(const Infos::BaseUserInfo& auth_rsp);
    const Infos::BaseUserInfo* GetFriendById(int uid);

private:
    SUserMgr()=default;
    QString Name;
    QString Token;
    int UId;
    QString Icon{ "" };
    std::unordered_map<int,Infos::BaseUserInfo> FriendMap;
};
#endif // USERMGR_H

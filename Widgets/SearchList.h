#ifndef CONTROL_SEARCHLIST_H
#define CONTROL_SEARCHLIST_H

#include "CustomList.h"
#include "Common/GlobalDefine.h"

class WReqApplyFriend;
class QListWidgetItem;
using namespace Infos;
class CSearchList: public ICustomList
{
    Q_OBJECT
public:
    CSearchList(QWidget* parent = nullptr);
    void CloseFindDlg();
    void SetSearchEdit(QWidget* edit);
    IUserInfoLstItem* MakeNewUserItem() override;
public slots:
    void slotUserSearch(const Infos::FSearchInfo& Info);
protected:
    void AfterSetListFunc() override;
    void SelfAddItems() override{};

private:
    WReqApplyFriend* FriendApplayWgt{ nullptr };
};

#endif // CONTROL_SEARCHLIST_H

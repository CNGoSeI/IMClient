#ifndef MAINCHATWGT_H
#define MAINCHATWGT_H

#include <qrect.h>

#include "Common/GlobalDefine.h"
#include "Common/LoadUIWgtBase.h"

class WApplyFriendPage;
class CSearchList;
class CChatUserList;
class WChatArea;
class WChatPage;
class WCloseTitle;
class QPushButton;
class QStackedWidget;
class QListWidget;
class QAction;
class QLineEdit;
class CContactUserList;

enum class EChatUIMode
{
    SearchMode, //搜索模式
    ChatMode, //聊天模式
    ContactMode, //联系人模式
};


class WChatWgt : public ILoadUIWgtBase
{
    Q_OBJECT

public:
    virtual ~WChatWgt();
    static WChatWgt& GetIns();
    void AddApplayFriendItem(const Infos::FAddFriendApply& Info,bool);//不提示红点的方式添加好友请求
    void AddConFriendItem(const Infos::BaseUserInfo& info);
    void SwitchToChatPage(const Infos::BaseUserInfo& info);//切换到聊天界面，并且设置聊天信息
    WChatPage* TryFindChatPage(int uid);//查找聊天界面，没有则添加
public slots:
    void slotTryFindUser();//搜索框的点击添加联系人之后，实行该函数
    void slotNotifyChatMsg(const QString& HtmlContent,const int UID,bool bSelf);
signals:
    void sigMainChatWgtSizeChanged();
    void sigClickedAddFriendArear();

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
    bool AddFriendEvent(QObject* watched, QEvent* event);
private:
    WChatWgt() = delete;
    explicit WChatWgt(QWidget* parent = nullptr);
    void InitControls() override;
    void ConnectSigSlot() override;
    void ShowSearch(bool bsearch = false);
    void HandleWindowResize(const QPoint& globalPos);//重设窗口大小
    void InitPages();
    void InitLists();
    void InitRedDots();

private:
    QLineEdit* Edt_Search{ nullptr };
    QAction* SearchAction{ nullptr };
    std::unique_ptr<CChatUserList>List_ChatUser{ nullptr };
    std::unique_ptr<CSearchList>List_Search{ nullptr };//搜索用户列表
    std::unique_ptr<CContactUserList> LstContactUser{ nullptr };

    QListWidget* List_ConUserr{ nullptr };//联系人列表
    QListWidget* Lst_SearchUser{ nullptr };
    QStackedWidget* StateWgt_List{ nullptr };
    QStackedWidget* Stacked_Right{ nullptr };//好友申请处理界面
    QWidget* Wgt_UserLst{ nullptr };
    QWidget* Wgt_SearchLst{ nullptr };
    QWidget* Wgt_ConLst{ nullptr };
    QWidget* Wgt_AddFriendAear{ nullptr };
    QLabel* Lab_HeadIcon{ nullptr };
    QPushButton* Btn_LineEdtClear{ nullptr };
    QPushButton* Btn_ResizeSizeFlag{ nullptr };//用来辅助界面缩放的按钮
    QPushButton* Btn_MsgModel{ nullptr };
    QPushButton* Btn_UserModel{ nullptr };
    QWidget* Wgt_WndTitle{ nullptr };
    WChatPage* ChatPage{ nullptr };//ChatPage.ui
    WCloseTitle* Wgt_CloseTitle{ nullptr };
    WApplyFriendPage* Wgt_ApplyFriendPage{ nullptr };

    EChatUIMode Mode{EChatUIMode::ChatMode };//当前界面显示的模式，聊天界面，联系人界面
    EChatUIMode State{ EChatUIMode::ChatMode };//不同模式(聊天界面、联系人界面)下存在搜索状态
    QPoint DragStartPos;//拖动操作在点击时的坐标
    QRect OriginalGeometry;//缩放操作开始时的窗口大小信息

    QLabel* Lab_RedDotMsg{ nullptr };
    QLabel* Lab_RedDotCon{ nullptr };
    QLabel* Lab_RedDotNewCon{ nullptr };

    std::unordered_map<int, WChatPage*>UId2ChatPage;//用户对应的聊天框

    const int ResizeBorderWidth = 20;//光标检测区域补正
    bool bInDragBtn{ false };//在拖拽按钮中
    bool bLoading{ false };//是否在加载用户信息中
};


#endif // MAINCHATWGT_H

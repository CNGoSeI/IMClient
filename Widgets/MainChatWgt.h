#ifndef MAINCHATWGT_H
#define MAINCHATWGT_H

#include <qrect.h>

#include "Common/GlobalDefine.h"
#include "Common/LoadUIWgtBase.h"

class WChatArea;
class WChatPage;
class WCloseTitle;
class QPushButton;
class QStackedWidget;
class QListWidget;
class ICustomList;
class QAction;
class QLineEdit;

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
    explicit WChatWgt(QWidget* parent = nullptr);
    virtual ~WChatWgt();

public slots:
    void slotLoadingChatUser();

signals:
    void sigMainChatWgtSizeChanged();
    void sigClickedAddFriendArear();

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
    bool AddFriendEvent(QObject* watched, QEvent* event);
private:
    void InitControls() override;
    void ConnectSigSlot() override;
    void ShowSearch(bool bsearch = false);
    void AddChatUserList();
    void HandleWindowResize(const QPoint& globalPos);//重设窗口大小

private:
    QLineEdit* Edt_Search{ nullptr };
    QAction* SearchAction{ nullptr };
    std::unique_ptr<ICustomList>List_ChatUser{ nullptr };
    std::unique_ptr<ICustomList>List_Search{ nullptr };//搜索用户列表
    QListWidget* List_ConUserr{ nullptr };//联系人列表
    QListWidget* Lst_SearchUser{ nullptr };
    QStackedWidget* StateWgt_List{ nullptr };
    QStackedWidget* Stacked_Right{ nullptr };
    QWidget* Wgt_UserLst{ nullptr };
    QWidget* Wgt_SearchLst{ nullptr };
    QWidget* Wgt_ConLst{ nullptr };
    QWidget* Wgt_AddFriendAear{ nullptr };
    QPushButton* Btn_LineEdtClear{ nullptr };
    QPushButton* Btn_ResizeSizeFlag{ nullptr };//用来辅助界面缩放的按钮
    QPushButton* Btn_MsgModel{ nullptr };
    QPushButton* Btn_UserModel{ nullptr };
    QWidget* Wgt_WndTitle{ nullptr };
    WChatPage* ChatPage{ nullptr };//ChatPage.ui
    WCloseTitle* Wgt_CloseTitle{ nullptr };

    EChatUIMode Mode{EChatUIMode::ChatMode };//当前界面显示的模式，聊天界面，联系人界面
    EChatUIMode State{ EChatUIMode::ChatMode };//不同模式(聊天界面、联系人界面)下存在搜索状态
    QPoint DragStartPos;//拖动操作在点击时的坐标
    QRect OriginalGeometry;//缩放操作开始时的窗口大小信息

    const int ResizeBorderWidth = 20;//光标检测区域补正
    bool bInDragBtn{ false };//在拖拽按钮中
    bool bLoading{ false };//是否在加载用户信息中
};


#endif // MAINCHATWGT_H

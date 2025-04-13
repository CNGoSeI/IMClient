#ifndef MAINCHATWGT_H
#define MAINCHATWGT_H

#include "Common/LoadUIWgtBase.h"

class QPushButton;
class QStackedWidget;
class QListWidget;
class CChatUserList;
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

private:
    void InitControls() override;
    void ConnectSigSlot() override;
    void ShowSearch(bool bsearch = false);
    void addChatUserList();

private:
    QLineEdit* Edt_Search{ nullptr };
    QAction* SearchAction{ nullptr };
    std::unique_ptr<CChatUserList>List_ChatUser{ nullptr };
    QListWidget* List_ConUserr{ nullptr };//联系人列表
    QListWidget* Lst_SearchUser{ nullptr };
    QStackedWidget* StateWgt_List{ nullptr };
    QWidget* Wgt_UserLst{ nullptr };
    QWidget* Wgt_SearchLst{ nullptr };
    QWidget* Wgt_ConLst{ nullptr };
    QPushButton* Btn_LineEdtClear{ nullptr };

    EChatUIMode Mode{EChatUIMode::ChatMode };//当前界面显示的模式，聊天界面，联系人界面
    EChatUIMode State{ EChatUIMode::ChatMode };//不同模式(聊天界面、联系人界面)下存在搜索状态
};


#endif // MAINCHATWGT_H

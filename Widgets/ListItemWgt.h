#ifndef LISTITEMWGT_H
#define LISTITEMWGT_H

#include "Common/LoadUIWgtBase.h"

class QListWidgetItem;

enum class EListItemType
{
    CHAT_USER_ITEM, //聊天用户
    CONTACT_USER_ITEM, //联系人用户
    SEARCH_USER_ITEM, //搜索到的用户
    ADD_USER_TIP_ITEM, //提示添加用户
    INVALID_ITEM,  //不可点击条目
    GROUP_TIP_ITEM, //分组提示条目
    LINE_ITEM,  //分割线
    APPLY_FRIEND_ITEM, //好友申请
};

class IListItemWgt: public ILoadUIWgtBase
{
    Q_OBJECT
public:
    explicit IListItemWgt(const QString& UIRes, EListItemType InItemType,QWidget* parent = nullptr);
    ~IListItemWgt() override = default;
    void SetItemType(EListItemType itemType) { ItemType = itemType;};
    EListItemType GetItemType() const { return ItemType; };
    virtual void BeClicked(QListWidgetItem* item) {};
    virtual void BeDoubelClicked(QListWidgetItem* item) {};
protected:
    EListItemType ItemType;
};

#endif // LISTITEMWGT_H

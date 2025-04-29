#ifndef CHATUSERWID_H
#define CHATUSERWID_H

/*
 *  聊天列表联系人的显示控件
 */
#include "UserInfoLstItem.h"

class CRedDotNode;
class QLabel;

class WChatUserWid: public IUserInfoLstItem
{
    Q_OBJECT
public:
	WChatUserWid(QWidget* parent=nullptr);
    ~WChatUserWid() override;
    void SetInfo(std::unique_ptr<Infos::BaseUserInfo> InInfo) override;
    void SetMessage(const QString& msg);
    void BeClicked(QListWidgetItem* item) override;
protected:
    void InitControls() override;

private:
    QString Name;
    QString Head;
    QString Msg;
    QLabel* Lab_Icon{ nullptr };
    QLabel* Lab_Time{ nullptr };
    QLabel* Lab_UserMsg{ nullptr };
    QLabel* Lab_UserName{ nullptr };
    QLabel* Lab_Red{ nullptr };
    CRedDotNode* RedControl{ nullptr };
};
#endif // CHATUSERWID_H

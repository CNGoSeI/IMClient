#ifndef CHATUSERWID_H
#define CHATUSERWID_H

#include "ListItemWgt.h"

class QLabel;

class WChatUserWid: public IListItemWgt
{
public:
	WChatUserWid(QWidget* parent=nullptr);
	void SetInfo(const QString& name, const QString& head, const QString& msg);

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

};
#endif // CHATUSERWID_H

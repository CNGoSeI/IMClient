#include "ChatUserWid.h"

#include <QLabel>
#include <qpixmap.h>

#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"

WChatUserWid::WChatUserWid(QWidget* parent) :
	IListItemWgt(WgtFile::ChatUserItem,EListItemType::CHAT_USER_ITEM,parent)
{

}

void WChatUserWid::InitControls()
{
	Lab_UserName = UIHelper::AssertFindChild<QLabel*>(GetUI(),"Lab_UserName");
	Lab_Icon = UIHelper::AssertFindChild<QLabel*>(GetUI(), "Lab_Icon");
	Lab_UserMsg = UIHelper::AssertFindChild<QLabel*>(GetUI(), "Lab_UserMsg");
	Lab_Time = UIHelper::AssertFindChild<QLabel*>(GetUI(), "Lab_Time");

}

void WChatUserWid::SetInfo(const QString& name, const QString& head, const QString& msg)
{
	Name = name;
	Head = head;
	Msg = msg;
	QPixmap Icon(head);

	Lab_Icon->setPixmap(Icon.scaled(Lab_Icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	Lab_Icon->setScaledContents(true);

	Lab_UserMsg->setText(msg);
	Lab_UserName->setText(name);
}


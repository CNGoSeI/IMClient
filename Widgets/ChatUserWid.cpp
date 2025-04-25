#include "ChatUserWid.h"

#include <QLabel>
#include <qpixmap.h>

#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"

WChatUserWid::WChatUserWid(QWidget* parent) :
	IUserInfoLstItem(WgtFile::ChatUserItem,EListItemType::CHAT_USER_ITEM,parent)
{

}

void WChatUserWid::SetInfo(std::unique_ptr<Infos::BaseUserInfo> InInfo)
{
	if (!InInfo)return;

	Name = InInfo->Name;
	Head = InInfo->HeadIconPath;
	QPixmap Icon(Head);

	Lab_Icon->setPixmap(Icon.scaled(Lab_Icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	Lab_Icon->setScaledContents(true);
	Lab_UserName->setText(Name);
}

void WChatUserWid::SetMessage(const QString& msg)
{
	Lab_UserMsg->setText(msg);
	Msg = msg;
}

void WChatUserWid::InitControls()
{
	Lab_UserName = UIHelper::AssertFindChild<QLabel*>(GetUI(),"Lab_UserName");
	Lab_Icon = UIHelper::AssertFindChild<QLabel*>(GetUI(), "Lab_Icon");
	Lab_UserMsg = UIHelper::AssertFindChild<QLabel*>(GetUI(), "Lab_UserMsg");
	Lab_Time = UIHelper::AssertFindChild<QLabel*>(GetUI(), "Lab_Time");

}


#include "ChatUserWid.h"

#include <QLabel>
#include <qpixmap.h>

#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"
#include "Common/RedDotNode.h"

static int RedCount{ 0 };

WChatUserWid::WChatUserWid(QWidget* parent) :
	IUserInfoLstItem(WgtFile::ChatUserItem,EListItemType::CHAT_USER_ITEM,parent)
{

}

WChatUserWid::~WChatUserWid()
{
	delete RedControl;
	RedControl = nullptr;
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

void WChatUserWid::BeClicked(QListWidgetItem* item)
{
	RedControl->NotifyShow(false);
}

void WChatUserWid::InitControls()
{
	Lab_UserName = UIHelper::AssertFindChild<QLabel*>(GetUI(),"Lab_UserName");
	Lab_Icon = UIHelper::AssertFindChild<QLabel*>(GetUI(), "Lab_Icon");
	Lab_UserMsg = UIHelper::AssertFindChild<QLabel*>(GetUI(), "Lab_UserMsg");
	Lab_Time = UIHelper::AssertFindChild<QLabel*>(GetUI(), "Lab_Time");
	Lab_Red= UIHelper::AssertFindChild<QLabel*>(GetUI(), "Lab_Red");
	Lab_Red->setVisible(false);

	RedControl = SRedDotMgr::Ins().CreateNode((QString("ChatMsg.") + UI->objectName()).toStdString(), [this](bool bShow)
	{
		Lab_Red->setVisible(bShow);
	});
	if (RedCount < 4)
	{
		Lab_Red->setVisible(true);
		RedControl->NotifyShow(true);
		RedCount++;
	}
}


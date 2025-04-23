#include "ApplyFriend.h"

#include <QLineEdit>
#include <QPushButton>

#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"
#include "Common/UserMgr.h"

WApplyFriend::WApplyFriend(QWidget* parent):
	ILoadUIWgtBase(WgtFile::AddFriendWgt,parent)
{
	UI->setWindowFlags(UI->windowFlags()/* | Qt::FramelessWindowHint*/ | Qt::Window);
	UI->setAttribute(Qt::WA_TranslucentBackground);//透明背景
}

void WApplyFriend::SetSearchInfo(const Infos::FSearchInfo& InInfo)
{
	Si = InInfo;
	QString applyname = SUserMgr::GetInstance().GetName();

	Edt_Name->setText(applyname);
	Edt_BackName->setText(Si.Name);
}

void WApplyFriend::InitControls()
{
	Edt_AddLab = UIHelper::AssertFindChild<QLineEdit*>(UI, "Edt_AddLab");
	Edt_BackName = UIHelper::AssertFindChild<QLineEdit*>(UI, "Edt_BackName");
	Edt_Name = UIHelper::AssertFindChild<QLineEdit*>(UI, "Edt_Name");
	Btn_Cancel= UIHelper::AssertFindChild<QPushButton*>(UI, "Btn_Cancel");
	Btn_OK = UIHelper::AssertFindChild<QPushButton*>(UI, "Btn_OK");

}

void WApplyFriend::ConnectSigSlot()
{
	connect(Btn_OK, &QPushButton::clicked, [this]()
	{
		UI->close();
		this->deleteLater();
	});

	connect(Btn_Cancel, &QPushButton::clicked, [this]()
	{
		UI->close();
		this->deleteLater();
	});
}

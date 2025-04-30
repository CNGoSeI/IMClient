#include "ChatPageWgt.h"

#include <qboxlayout.h>
#include <QPushButton>
#include <QWidget>
#include <QSplitter>
#include <QTextEdit>

#include "ChatArea.h"
#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"
#include "InputTextEdit.h"
#include "Common/RedDotNode.h"

WChatPage::WChatPage(QWidget* parent):
	ILoadUIWgtBase(WgtFile::ChatPageWgt,parent)
{
}

void WChatPage::slotMainChatSizeChanged()
{
	ChatAreaControl->slotChangeSizeed();

}

void WChatPage::InitControls()
{
	Wgt_ChatArea = UIHelper::AssertFindChild<QWidget*>(UI, "Wgt_ChatArea");
	Wgt_ChatArea->setLayout(new QVBoxLayout());
	ChatAreaControl = new WChatArea(Wgt_ChatArea);
	ChatAreaControl->CreateWgt();
	Wgt_ChatArea->layout()->addWidget(ChatAreaControl->GetUI());

	Btn_Send = UIHelper::AssertFindChild<QPushButton*>(UI, "Btn_Send");
	Btn_Recive = UIHelper::AssertFindChild<QPushButton*>(UI, "Btn_Recive");

	Wgt_EditChat = UIHelper::AssertFindChild<QWidget*>(UI, "Wgt_EditChat");
	Wgt_EditChat->setLayout(new QVBoxLayout);
	
	Edt_Chat= new CInputTextEdit(UI);
	Edt_Chat->setObjectName("Edt_Chat");
	Wgt_EditChat->layout()->addWidget(Edt_Chat);

	splitter = UIHelper::AssertFindChild<QSplitter*>(UI,"splitter");
	splitter->setStretchFactor(0, 1);
	splitter->setStretchFactor(1, 3);
}

void WChatPage::ConnectSigSlot()
{
	connect(Btn_Send, &QPushButton::clicked, this, [this]()
	{
		QString htmlContent = Edt_Chat->toHtml();
		if (htmlContent.isEmpty())return;
		ChatAreaControl->AddMsgItem(true, htmlContent.toUtf8());
		Edt_Chat->clear();
	});

	connect(Btn_Recive, &QPushButton::clicked, this, [this]()
	{
		QString htmlContent = Edt_Chat->toHtml();
		if (htmlContent.isEmpty())return;
		ChatAreaControl->AddMsgItem(false, htmlContent.toUtf8());
		Edt_Chat->clear();
		static int index{ 1 };
		QString TotalName = QString("ChatMsg.%1_%2").arg("ChatUserWid").arg(index);
		SRedDotMgr::Ins().NotifyTargetShow(true,TotalName.toStdString());
		index++;
		if (index > 4)index = 1;
	});
}

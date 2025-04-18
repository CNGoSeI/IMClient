#include "ChatPageWgt.h"

#include <qboxlayout.h>
#include <QPushButton>
#include <QWidget>
#include <QSplitter>
#include <QTextEdit>

#include "ChatArea.h"
#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"

WChatPage::WChatPage(QWidget* parent):
	ILoadUIWgtBase(WgtFile::ChatPageWgt,parent)
{
}

void WChatPage::InitControls()
{
	Wgt_ChatArea = UIHelper::AssertFindChild<QWidget*>(UI, "Wgt_ChatArea");
	Wgt_ChatArea->setLayout(new QVBoxLayout());
	ChatAreaControl = new WChatArea(Wgt_ChatArea);
	ChatAreaControl->CreateWgt();
	Wgt_ChatArea->layout()->addWidget(ChatAreaControl->GetUI());

	Btn_Send = UIHelper::AssertFindChild<QPushButton*>(UI, "Btn_Send");

	Edt_Chat= UIHelper::AssertFindChild<QTextEdit*>(UI, "Edt_Chat");

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
	});
}

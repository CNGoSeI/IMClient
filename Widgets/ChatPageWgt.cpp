#include "ChatPageWgt.h"

#include <qboxlayout.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QSplitter>
#include <QTextEdit>

#include "ChatArea.h"
#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"
#include "InputTextEdit.h"
#include "MainChatWgt.h"
#include "Common/RedDotNode.h"
#include "Common/TcpMgr.h"
#include "Common/UserMgr.h"

WChatPage::WChatPage(QWidget* parent):
	ILoadUIWgtBase(WgtFile::ChatPageWgt,parent)
{
}

void WChatPage::SetTargetInfo(const Infos::BaseUserInfo& info)
{
	ChatTarget = info;
	Lab_Title->setText(info.Name);
}

void WChatPage::AddMessage(const QString& HtmlCon, bool bSelf)
{
	ChatAreaControl->AddMsgItem(bSelf, HtmlCon.toUtf8());
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

	Lab_Title = UIHelper::AssertFindChild<QLabel*>(UI, "Lab_Title");

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
		WChatWgt::GetIns().slotNotifyChatMsg(htmlContent, ChatTarget.UID,true);
		QJsonObject textObj;
		textObj["fromuid"] = SUserMgr::GetInstance().GetUid();
		textObj["touid"] = ChatTarget.UID;
		textObj["text_array"] = htmlContent;
		QJsonDocument doc(textObj);
		QByteArray jsonData = doc.toJson(QJsonDocument::Compact);
		emit STcpMgr::GetInstance().sigSendData(ReqID::ID_TEXT_CHAT_MSG_REQ, jsonData);
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

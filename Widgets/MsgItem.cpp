#include "MsgItem.h"

#include <qcoreevent.h>
#include <QTextEdit>
#include <QKeyEvent>
#include <QLabel>
#include <QScrollBar>

#include "Common/GlobalDefine.h"
#include "Widgets/WidgetFilesHelper.h"
#include <QTextBrowser>

WMsgItem::WMsgItem(bool bIsSelf, const QByteArray& HtmlData, QWidget* parent):
	ILoadUIWgtBase(bIsSelf?WgtFile::SelfMsgItem:WgtFile::OtherMsgItem,parent),
	Message(HtmlData)
{

}

void WMsgItem::InitControls()
{
	Wgt_Msg= UIHelper::AssertFindChild<QWidget*>(UI, "Wgt_Msg");
	Lab_Name = UIHelper::AssertFindChild<QLabel*>(UI, "Lab_Name");

	Edit_MsgContent = UIHelper::AssertFindChild<QTextBrowser*>(UI, "Edit_MsgContent");


	auto tempWrap = Edit_MsgContent->wordWrapMode();

	Edit_MsgContent->setHtml(QString::fromUtf8(Message));
	Edit_MsgContent->setWordWrapMode(QTextOption::NoWrap);	// 禁用自动换行以获取真实内容宽度（避免换行影响宽度计算）

	Edit_MsgContent->document()->adjustSize();// 强制更新文档布局（确保尺寸计算准确）
	UI->adjustSize();

	// 获取内容理想宽度（包含边距）
	int contentWidth = Edit_MsgContent->document()->idealWidth();
		//+ Edit_MsgContent->contentsMargins().left()
		//+ Edit_MsgContent->contentsMargins().right();
	int contentHeight = Edit_MsgContent->document()->size().height();
	//int labelWidth = Lab_Name->width();
	//int totalWidth = labelWidth + contentWidth;
	Edit_MsgContent->setMaximumSize(contentWidth, contentHeight);
	//Edit_MsgContent->setSizePolicy();
	//Edit_MsgContent
	Edit_MsgContent->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

	UI->setMaximumHeight(contentWidth + 20);
	UI->adjustSize();
	//不让滚动
	Edit_MsgContent->verticalScrollBar()->setEnabled(false); 
	Edit_MsgContent->horizontalScrollBar()->setEnabled(false);
}

void WMsgItem::ConnectSigSlot()
{
	
}

bool WMsgItem::eventFilter(QObject* watched, QEvent* event)
{

	return ILoadUIWgtBase::eventFilter(watched, event);
}

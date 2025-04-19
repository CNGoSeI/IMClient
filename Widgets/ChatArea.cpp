#include "ChatArea.h"

#include <qcoreevent.h>
#include <QLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QTimer>

#include "MsgItem.h"
#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"
#include "Common/LoadUIWgtBase.h"

WChatArea::WChatArea(QWidget* parent):
	ILoadUIWgtBase(WgtFile::ChatDataArea,parent)
{
}

WChatArea::~WChatArea()
{
}

bool WChatArea::eventFilter(QObject* watched, QEvent* event)
{
	return QObject::eventFilter(watched, event);
}

void WChatArea::InitControls()
{
	Wgt_Scroll=UIHelper::AssertFindChild<QWidget*>(UI, "Wgt_Scroll");

	ScrollArea = UIHelper::AssertFindChild<QScrollArea*>(UI, "ScrollArea");
	ScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

void WChatArea::ConnectSigSlot()
{
	connect(ScrollArea->verticalScrollBar(), &QScrollBar::rangeChanged, this, &WChatArea::slotVScrollBarMoved);
}

void WChatArea::AddMsgItem(bool bIsSelf, const QByteArray& HtmlContent)
{
	auto tempWgt = new WMsgItem(true, HtmlContent, Wgt_Scroll);
	tempWgt->CreateWgt();
	bAppended = true;

	auto* vl = qobject_cast<QVBoxLayout*>(Wgt_Scroll->layout());
	vl->insertWidget(ChirdenMsgItems.size(), tempWgt->GetUI());
	ChirdenMsgItems.emplace(tempWgt);

	connect(tempWgt, &WMsgItem::sigDie, this, [this](WMsgItem* Dieder)
	{
		auto it = ChirdenMsgItems.find(Dieder);
		if (it != ChirdenMsgItems.end())
		{
			ChirdenMsgItems.erase(it);
		}
	});
}

void WChatArea::slotChangeSizeed()
{
	for(auto it: ChirdenMsgItems)
	{
		it->ResizeRect();
	}

}

void WChatArea::slotVScrollBarMoved(int min, int max)
{
	if (bAppended) //添加item可能调用多次
	{
		QScrollBar* pVScrollBar = ScrollArea->verticalScrollBar();
		pVScrollBar->setSliderPosition(pVScrollBar->maximum());
		pVScrollBar->setVisible(max > 0);

		//500毫秒内可能调用多次
		QTimer::singleShot(500, [this]()
		{
			bAppended = false;
		});
	}

}

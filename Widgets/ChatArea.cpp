#include "ChatArea.h"

#include <qcoreevent.h>
#include <QLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QTimer>

#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"

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
	Wgt_Scroll=UIHelper::AssertFindChild<QScrollArea*>(UI, "Wgt_Scroll");
	Layout_Scroll = UIHelper::AssertFindChild<QVBoxLayout*>(UI, "Layout_Scroll");
	ScrollArea = UIHelper::AssertFindChild<QScrollArea*>(UI, "ScrollArea");
	ScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//ScrollArea->installEventFilter(this);

	for(int i=0;i<50;++i)
	{
		Layout_Scroll->addWidget(new QPushButton());
	}
}

void WChatArea::ConnectSigSlot()
{
	connect(ScrollArea->verticalScrollBar(), &QScrollBar::rangeChanged, this, &WChatArea::slotVScrollBarMoved);
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

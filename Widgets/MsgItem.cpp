#include "MsgItem.h"

#include <qcoreevent.h>
#include <QTextEdit>
#include <QKeyEvent>
#include <QLayout>
#include <QLabel>
#include <QPainter>
#include <QScrollBar>
#include <QTextBlock>
#include <QSpacerItem>

#include "Common/GlobalDefine.h"
#include "Widgets/WidgetFilesHelper.h"
#include <QTextBrowser>
#include <QTimer>

const int WIDTH_SANJIAO = 8;

WMsgItem::WMsgItem(bool bIsSelf, const QByteArray& HtmlData, QWidget* parent):
	ILoadUIWgtBase(bIsSelf?WgtFile::SelfMsgItem:WgtFile::OtherMsgItem,parent),
	Message(HtmlData),
	bSelfMsg(bIsSelf)
{

}

WMsgItem::~WMsgItem()
{
	emit sigDie(this);
}

double WMsgItem::ResizeRect()
{
	//下次消息循环再执行
	QTimer::singleShot(0, this, [this]
	{
		QTextDocument* doc = Edit_MsgContent->document();
		doc->adjustSize(); // 强制更新文档布局[6,8](@ref)

		// 设置文档宽度与控件可视宽度一致（排除滚动条和边距）
		int viewportWidth = Edit_MsgContent->viewport()->width();
		doc->setTextWidth(viewportWidth);

		// 计算实际内容高度（包含边距）
		qreal doc_margin = Edit_MsgContent->document()->documentMargin();
		int vMargin = UI->layout()->contentsMargins().top();
		auto DocH = Edit_MsgContent->document()->size().height();
		UI->setFixedHeight(DocH + doc_margin * 2 + vMargin * 2 + 35);
	});

	return 0.0;
}

void WMsgItem::InitControls()
{
	Lab_Name = UIHelper::AssertFindChild<QLabel*>(UI, "Lab_Name");

	Edit_MsgContent = UIHelper::AssertFindChild<QTextBrowser*>(UI, "Edit_MsgContent");
	Edit_MsgContent->setHtml(QString::fromUtf8(Message));
	Edit_MsgContent->setWordWrapMode(QTextOption::NoWrap); // 禁用自动换行以获取真实内容宽度（避免换行影响宽度计算）
	Edit_MsgContent->document()->adjustSize(); // 强制更新文档布局（确保尺寸计算准确）
	// 获取内容理想宽度（包含边距）
	auto contentWidth = Edit_MsgContent->document()->idealWidth()
		+ Edit_MsgContent->contentsMargins().left()
		+ Edit_MsgContent->contentsMargins().right()
		+ 20;
	Edit_MsgContent->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
	Edit_MsgContent->setMaximumWidth(contentWidth);

	qreal doc_margin = Edit_MsgContent->document()->documentMargin();
	int vMargin = UI->layout()->contentsMargins().top();
	auto DocH = Edit_MsgContent->document()->size().height();
	double H = DocH + doc_margin * 2 + vMargin * 2 + 45;
	UI->setMinimumHeight(H);

	//第一次触发一些大小计算，刚开始可能不准，因此延后执行
	QTimer::singleShot(10, [this]()
	{
		ResizeRect();
	});
	
	//不让滚动
	Edit_MsgContent->verticalScrollBar()->setEnabled(false);
	Edit_MsgContent->horizontalScrollBar()->setEnabled(false);
	Edit_MsgContent->installEventFilter(this);
}

void WMsgItem::ConnectSigSlot()
{
	
}

bool WMsgItem::eventFilter(QObject* watched, QEvent* event)
{
	if (watched == Edit_MsgContent)
	{
		if (event->type() == QEvent::Paint)
		{
			// 自定义绘制流程
			QPainter painter(Edit_MsgContent);
			DrawBubbleBackground(Edit_MsgContent, &painter);
			return true; // 已处理绘制事件
		}
		if (event->type() == QEvent::LayoutRequest)
		{
			qreal doc_margin = Edit_MsgContent->document()->documentMargin();
			int vMargin = UI->layout()->contentsMargins().top();
			auto DocH = Edit_MsgContent->document()->size().height();
			UI->setMaximumHeight(Edit_MsgContent->height() + doc_margin * 2 + vMargin * 2 + 45);
		}
	}

	return ILoadUIWgtBase::eventFilter(watched, event);
}

void WMsgItem::DrawBubbleBackground(QWidget* edit, QPainter* painter)
{
	painter->setPen(Qt::NoPen);
	static QColor bk_color = UIHelper::GetTargetColor("MsgItem");
	painter->setBrush(QBrush(bk_color));

	if (!bSelfMsg)
	{
		painter->setBrush(QBrush(bk_color));
		QRect bk_rect = QRect(WIDTH_SANJIAO, 0, Edit_MsgContent->width() - WIDTH_SANJIAO, Edit_MsgContent->height());
		painter->drawRoundedRect(bk_rect, 5, 5);
		//画小三角
		QPointF points[3] = {
			QPointF(bk_rect.x(), 12),
			QPointF(bk_rect.x(), 10 + WIDTH_SANJIAO + 2),
			QPointF(bk_rect.x() - WIDTH_SANJIAO, 10 + WIDTH_SANJIAO - WIDTH_SANJIAO / 2),
		};
		painter->drawPolygon(points, 3);
	}
	else
	{
		painter->setBrush(QBrush(bk_color));
		//画气泡
		QRect bk_rect = QRect(0, 0, Edit_MsgContent->width() - WIDTH_SANJIAO, Edit_MsgContent->height());
		painter->drawRoundedRect(bk_rect, 5, 5);
		//画三角
		QPointF points[3] = {
			QPointF(bk_rect.x() + bk_rect.width(), 12),
			QPointF(bk_rect.x() + bk_rect.width(), 12 + WIDTH_SANJIAO + 2),
			QPointF(bk_rect.x() + bk_rect.width() + WIDTH_SANJIAO, 10 + WIDTH_SANJIAO - WIDTH_SANJIAO / 2),
		};
		painter->drawPolygon(points, 3);
	}
}

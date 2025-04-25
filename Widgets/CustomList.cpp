#include "CustomList.h"

#include <QWheelEvent>
#include <QScrollBar>
#include <QListWidget>

ICustomList::ICustomList(QWidget* parent):
	QObject(parent)
{
    Q_UNUSED(parent);

}

void ICustomList::SetListWgt(QListWidget* Target)
{
	if (!Target)return;
	ListWgt = Target;

	ListWgt->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ListWgt->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	// 安装事件过滤器
	ListWgt->viewport()->installEventFilter(this);

	AfterSetListFunc();
}

void ICustomList::AddInfoItem(Infos::BaseUserInfo* Info)
{

}

bool ICustomList::eventFilter(QObject* watched, QEvent* event)
{
	if (watched == ListWgt->viewport())
	{
		if (event->type() == QEvent::Enter)
		{
			// 鼠标悬浮，显示滚动条
			ListWgt->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
		}
		else if (event->type() == QEvent::Leave)
		{
			// 鼠标离开，隐藏滚动条
			ListWgt->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		}

		if (event->type() == QEvent::Wheel)
		{
			QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);
			int numDegrees = wheelEvent->angleDelta().y() / 8;
			int numSteps = numDegrees / 15; // 计算滚动步数

			// 设置滚动幅度
			ListWgt->verticalScrollBar()->setValue(ListWgt->verticalScrollBar()->value() - numSteps);

			// 检查是否滚动到底部
			QScrollBar* scrollBar = ListWgt->verticalScrollBar();
			int maxScrollValue = scrollBar->maximum();
			int currentValue = scrollBar->value();

			AppendWheelEvent(wheelEvent, maxScrollValue, currentValue);
			return true; // 停止事件传递
		}

	}


	return QObject::eventFilter(watched, event);
}

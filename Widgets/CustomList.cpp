#include "CustomList.h"

#include <QWheelEvent>
#include <QScrollBar>
#include <QListWidget>

#include "UserInfoLstItem.h"
#include "Common/GlobalDefine.h"

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

	connect(ListWgt, &QListWidget::itemClicked, [this](QListWidgetItem* item)
	{
		QWidget* itemWidget = ListWgt->itemWidget(item);
		if (auto ItemWgt = ILoadUIWgtBase::GetOwner<IListItemWgt>(itemWidget))
		{
			ItemWgt->BeClicked(item);
		}
	});

	// 安装事件过滤器
	ListWgt->viewport()->installEventFilter(this);

	AfterSetListFunc();
}

IUserInfoLstItem* ICustomList::AddInfoItem(std::unique_ptr<Infos::BaseUserInfo> Info)
{
	auto* add_user_item = MakeNewUserItem();
	add_user_item->CreateWgt();
	add_user_item->SetInfo(std::move(Info));
	QListWidgetItem* item = new QListWidgetItem;
	item->setSizeHint(add_user_item->GetUI()->sizeHint());
	ListWgt->addItem(item);
	ListWgt->setItemWidget(item, add_user_item->GetUI());

	return add_user_item;
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
		else if (event->type() == QEvent::Wheel)
		{
			QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);
			int numDegrees = wheelEvent->angleDelta().y() / 8;
			int numSteps = numDegrees / 15; // 计算滚动步数

			// 设置滚动幅度
			ListWgt->verticalScrollBar()->setValue(ListWgt->verticalScrollBar()->value() - numSteps);

			QScrollBar* scrollBar = ListWgt->verticalScrollBar();
			AppendWheelEvent(wheelEvent, scrollBar->maximum(), scrollBar->value());

			return false; // 停止事件传递
		}

	}


	return QObject::eventFilter(watched, event);
}

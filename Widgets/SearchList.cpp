#include "SearchList.h"

#include <QListWidget>

#include "AddUserItem.h"
#include "Common/TcpMgr.h"

CSearchList::CSearchList(QWidget* parent):
	ICustomList(parent)
{
}

void CSearchList::AfterSetListFunc()
{
	connect(ListWgt, &QListWidget::itemClicked, this, &CSearchList::slotItemClicked);

	AddTipItem();

	//连接搜索条目
	//connect(&STcpMgr::GetInstance(), &STcpMgr::sigSearch, this, &CSearchList::slot_user_search);
}

void CSearchList::AddTipItem()
{
    //auto* InValidWgt = new QWidget();
    //QListWidgetItem* item_tmp = new QListWidgetItem;
    ////qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
    ////item_tmp->setSizeHint(QSize(ListWgt->width(), 10));
    //ListWgt->addItem(item_tmp);
    //InValidWgt->setObjectName("invalid_item");
    //ListWgt->setItemWidget(item_tmp, InValidWgt);
    //item_tmp->setFlags(item_tmp->flags() & ~Qt::ItemIsSelectable);

    auto* add_user_item = new CAddUserItem();
    add_user_item->CreateWgt();
    QListWidgetItem* item = new QListWidgetItem;
    //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
    ListWgt->addItem(item);
    ListWgt->setItemWidget(item, add_user_item->GetUI());
}

void CSearchList::slotItemClicked(QListWidgetItem* item)
{
}

#ifndef CONTORL_CUSTOMLIST_H
#define CONTORL_CUSTOMLIST_H

#include <QObject>

class IUserInfoLstItem;

namespace Infos
{
	struct BaseUserInfo;
}

class QListWidgetItem;
class QWheelEvent;
class QListWidget;

class ICustomList : public QObject
{
	Q_OBJECT
public:
	ICustomList(QWidget* parent = nullptr);
	void SetListWgt(QListWidget* Target);
	IUserInfoLstItem* AddInfoItem(std::unique_ptr<Infos::BaseUserInfo> Info);
protected:
	bool eventFilter(QObject* watched, QEvent* event) override;
	virtual void AppendWheelEvent(QWheelEvent* event,int,int){};//滚到最新处需要执行的函数
	virtual void AfterSetListFunc(){};//设置listwgt之后执行的函数
	virtual void SelfAddItems(){};
	virtual IUserInfoLstItem* MakeNewUserItem() = 0;
	virtual void LoadingItems(){};//通知控件加载子项
signals:
	

public:
	QListWidget* ListWgt{nullptr};

protected:
	bool bLoading{ false };
};

#endif // CHATUSERLIST_H
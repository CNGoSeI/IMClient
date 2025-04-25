#ifndef CONTORL_CUSTOMLIST_H
#define CONTORL_CUSTOMLIST_H

#include <QObject>

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
	void AddInfoItem(Infos::BaseUserInfo* Info);
protected:
	bool eventFilter(QObject* watched, QEvent* event) override;
	virtual void AppendWheelEvent(QWheelEvent* event,int,int){};//滚到最新处需要执行的函数
	virtual void AfterSetListFunc(){};//设置listwgt之后执行的函数
	virtual void SelfAddItems(){};
signals:
	void sigLoadingItems();//通知控件加载子项

public:
	QListWidget* ListWgt{nullptr};

protected:
	bool bLoading{ false };
};

#endif // CHATUSERLIST_H
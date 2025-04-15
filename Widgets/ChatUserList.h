#ifndef CHATUSERLIST_H
#define CHATUSERLIST_H
#include <QObject>

class QListWidget;

class CChatUserList : public QObject
{
	Q_OBJECT

public:
	CChatUserList(QWidget* parent = nullptr);
	void SetListWgt(QListWidget* Target);

protected:
	bool eventFilter(QObject* watched, QEvent* event) override;

signals:
	void sigLoadingChatUser();//通知控件加载子项

public:
	QListWidget* ListWgt{nullptr};
};
#endif // CHATUSERLIST_H

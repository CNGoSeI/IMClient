#ifndef WGT_CHATAREA_H
#define WGT_CHATAREA_H

#include "Common/LoadUIWgtBase.h"
#include <set>

class WMsgItem;
class QVBoxLayout;
class QScrollArea;

class WChatArea:public ILoadUIWgtBase
{
	Q_OBJECT
public:
	WChatArea(QWidget* parent);

	~WChatArea() override;

protected:
	bool eventFilter(QObject* watched, QEvent* event) override;
	void InitControls() override;
	void ConnectSigSlot() override;

public:
	void AddMsgItem(bool bIsSelf,const QByteArray& HtmlContent);
public slots:
	void slotChangeSizeed();
private slots:
	void slotVScrollBarMoved(int min, int max);

private:
	QWidget* Wgt_Scroll{ nullptr };
	QWidget* Wgt_ItemContent{ nullptr };
	QScrollArea* ScrollArea{ nullptr };
	QVBoxLayout* Layout_Scroll{ nullptr };
	bool bAppended{ false };

	std::set<WMsgItem*>ChirdenMsgItems;
};
#endif // WGT_CHATAREA_H

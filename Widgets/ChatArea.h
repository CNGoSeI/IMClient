#ifndef WGT_CHATAREA_H
#define WGT_CHATAREA_H

#include "Common/LoadUIWgtBase.h"

class QVBoxLayout;
class QScrollArea;

class WChatArea:public ILoadUIWgtBase
{
public:
	WChatArea(QWidget* parent);

	~WChatArea() override;

protected:
	bool eventFilter(QObject* watched, QEvent* event) override;
	void InitControls() override;
	void ConnectSigSlot() override;

public:
	void AddMsgItem(bool bIsSelf,const QByteArray& HtmlContent);
private slots:
	void slotVScrollBarMoved(int min, int max);
private:
	QWidget* Wgt_Scroll{ nullptr };
	QScrollArea* ScrollArea{ nullptr };
	QVBoxLayout* Layout_Scroll{ nullptr };
	bool bAppended{ false };
};
#endif // WGT_CHATAREA_H

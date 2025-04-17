#ifndef WGT_CHATPAGEWGT_H
#define WGT_CHATPAGEWGT_H
#include "Common/LoadUIWgtBase.h"

class WChatArea;
class QSplitter;

class WChatPage:public ILoadUIWgtBase
{
public:
	WChatPage(QWidget* parent);
	~WChatPage() override=default;

protected:
	void InitControls() override;
	void ConnectSigSlot() override;

private:
	QWidget* Wgt_ChatArea{ nullptr };
	QSplitter* splitter{nullptr};
	WChatArea* ChatAreaControl{ nullptr };
};
#endif // WGT_CHATPAGEWGT_H

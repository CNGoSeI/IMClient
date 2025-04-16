#ifndef WGT_CHATPAGEWGT_H
#define WGT_CHATPAGEWGT_H
#include "Common/LoadUIWgtBase.h"

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
	QSplitter* splitter{nullptr};
};
#endif // WGT_CHATPAGEWGT_H

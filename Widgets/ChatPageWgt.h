#ifndef WGT_CHATPAGEWGT_H
#define WGT_CHATPAGEWGT_H
#include "Common/LoadUIWgtBase.h"

class QPushButton;
class WChatArea;
class QSplitter;
class QTextEdit;

class WChatPage :public ILoadUIWgtBase
{
public:
	WChatPage(QWidget* parent);
	~WChatPage() override = default;

protected:
	void InitControls() override;
	void ConnectSigSlot() override;

private:
	QWidget* Wgt_ChatArea{ nullptr };
	QSplitter* splitter{ nullptr };
	WChatArea* ChatAreaControl{ nullptr };
	QPushButton* Btn_Send{ nullptr };
	QTextEdit* Edt_Chat{ nullptr };//¡ƒÃÏ ‰»ÎøÚ
};
#endif // WGT_CHATPAGEWGT_H

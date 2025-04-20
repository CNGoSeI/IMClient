#ifndef WGT_CHATPAGEWGT_H
#define WGT_CHATPAGEWGT_H
#include "Common/LoadUIWgtBase.h"

class QPushButton;
class WChatArea;
class QSplitter;
class QTextEdit;
class CInputTextEdit;

class WChatPage :public ILoadUIWgtBase
{
	Q_OBJECT
public:
	WChatPage(QWidget* parent);
	~WChatPage() override = default;

public slots:
	void slotMainChatSizeChanged();

protected:
	void InitControls() override;
	void ConnectSigSlot() override;

private:
	QWidget* Wgt_ChatArea{ nullptr };
	QWidget* Wgt_EditChat{ nullptr };
	QSplitter* splitter{ nullptr };
	WChatArea* ChatAreaControl{ nullptr };
	QPushButton* Btn_Send{ nullptr };
	QPushButton* Btn_Recive{ nullptr };
	CInputTextEdit* Edt_Chat{ nullptr };//聊天输入框
};
#endif // WGT_CHATPAGEWGT_H

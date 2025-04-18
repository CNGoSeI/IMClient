#ifndef WGT_MSGITEM_H
#define WGT_MSGITEM_H

#include "Common/LoadUIWgtBase.h"

class QTextBrowser;
class QLabel;
class QTextEdit;

class WMsgItem:public ILoadUIWgtBase
{
public:
	WMsgItem(bool bIsSelf,const QByteArray& HtmlData,QWidget* parent);
	~WMsgItem() override=default;

	QByteArray Message{ 0 };
protected:
	void InitControls() override;
	void ConnectSigSlot() override;
	bool eventFilter(QObject* watched, QEvent* event) override;
private:
	QTextBrowser* Edit_MsgContent{ nullptr };
	QWidget* Wgt_Msg{ nullptr };
	QLabel* Lab_Name{ nullptr };
};
#endif // WGT_MSGITEM_H

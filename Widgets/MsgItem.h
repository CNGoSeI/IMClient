#ifndef WGT_MSGITEM_H
#define WGT_MSGITEM_H

#include <qpainter.h>

#include "Common/LoadUIWgtBase.h"

class QTextBrowser;
class QLabel;
class QTextEdit;
class QSpacerItem;

class WMsgItem:public ILoadUIWgtBase
{
	Q_OBJECT
public:
	WMsgItem(bool bIsSelf,const QByteArray& HtmlData,QWidget* parent);
	~WMsgItem() override;

	double ResizeRect();

	QByteArray Message{ 0 };

signals:
		void sigDie(WMsgItem*);
protected:
	void InitControls() override;
	void ConnectSigSlot() override;
	bool eventFilter(QObject* watched, QEvent* event) override;
	void DrawBubbleBackground(QWidget* edit, QPainter* painter);

private:
	bool bSelfMsg{ true };
	QTextBrowser* Edit_MsgContent{ nullptr };
	QWidget* Wgt_MsgItemBack{ nullptr };
	QLabel* Lab_Name{ nullptr };
	QSpacerItem* Spacer_MsgBuf{ nullptr };
};
#endif // WGT_MSGITEM_H

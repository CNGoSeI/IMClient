#ifndef CLOSETITLEWGT_H
#define CLOSETITLEWGT_H

#include <qrect.h>

#include "Common/LoadUIWgtBase.h"

class QPushButton;

class WCloseTitle:public ILoadUIWgtBase
{
public:
	WCloseTitle(QWidget* parent=nullptr);

	~WCloseTitle() override;

protected:
	void InitControls() override;
	void ConnectSigSlot() override;

private:
	QPushButton* Btn_Close{ nullptr };
	QPushButton* Btn_Max{ nullptr };
	QPushButton* Btn_Min{ nullptr };
	QWidget* FollowedWgt{ nullptr };
	QRect normalGeometry;
};

#endif // CLOSETITLEWGT_H

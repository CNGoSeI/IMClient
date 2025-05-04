#ifndef WGT_APPLYFRIEND_H
#define WGT_APPLYFRIEND_H

/* 好友申请界面 */
#include "Common/GlobalDefine.h"
#include "Common/LoadUIWgtBase.h"

class QPushButton;
class QLineEdit;

class WReqApplyFriend:public ILoadUIWgtBase
{
	Q_OBJECT
public:
	WReqApplyFriend(QWidget* parent=nullptr);

	~WReqApplyFriend() override=default;
	void SetSearchInfo(const Infos::FSearchInfo& InInfo);

protected:
	void InitControls() override;
	void ConnectSigSlot() override;
	void ApplySure() const;//确认申请好友

private:
	//void ResetLabels();

	QLineEdit* Edt_Name{ nullptr };
	QLineEdit* Edt_BackName{ nullptr };
	QLineEdit* Edt_AddLab{ nullptr };
	QPushButton* Btn_OK{ nullptr };
	QPushButton* Btn_Cancel{ nullptr };
	Infos::FSearchInfo Si{0,"","","",0};//搜索的用户信息结构体
};
#endif // WGT_APPLYFRIEND_H

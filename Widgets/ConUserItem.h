#ifndef WGT_CONUSERITEM_H
#define WGT_CONUSERITEM_H
/* 联系人列表的Item */
#include "ListItemWgt.h"

class QLabel;

class WConUserItem: public IListItemWgt
{
	Q_OBJECT
public:
	WConUserItem(QWidget* parent);
	void SetInfo(const QString& Name, const QString& Slogen, const QString& IconPath);
protected:
	void InitControls() override;
	void ConnectSigSlot() override;

public:
	~WConUserItem() override;

private:
	QLabel* Lab_BigName{nullptr};
	QLabel* Lab_UserSlogen{ nullptr };//宣言
	QLabel* Lab_Icon{ nullptr };
};
#endif // WGT_CONUSERITEM_H

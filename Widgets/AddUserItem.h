#ifndef CONTROL_ADDUSERITEM_H
#define CONTROL_ADDUSERITEM_H
#include "ListItemWgt.h"

class CAddUserItem: public IListItemWgt
{
	Q_OBJECT
public:
	CAddUserItem(QWidget* parent = nullptr);
protected:
	void InitControls() override;
};
#endif // control_ADDUSERITEM_H

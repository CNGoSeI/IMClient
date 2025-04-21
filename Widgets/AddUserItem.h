#ifndef control_ADDUSERITEM_H
#define control_ADDUSERITEM_H
#include "ListItemWgt.h"

class CAddUserItem: public IListItemWgt
{
public:
	CAddUserItem(QWidget* parent = nullptr);
protected:
	void InitControls() override;
};
#endif // control_ADDUSERITEM_H

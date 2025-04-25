#ifndef CONTROL_USERINFOLSTITEM_H
#define CONTROL_USERINFOLSTITEM_H
#include "ListItemWgt.h"
#include "Common/GlobalDefine.h"
namespace Infos
{
	struct BaseUserInfo;
}

class IUserInfoLstItem: public IListItemWgt
{
	Q_OBJECT
public:
	explicit IUserInfoLstItem(const QString& UIRes, EListItemType InItemType, QWidget* parent = nullptr);
	virtual void SetInfo(std::unique_ptr<Infos::BaseUserInfo> InInfo) = 0;//小心Info内存泄漏
	virtual ~IUserInfoLstItem();

protected:
	std::unique_ptr<Infos::BaseUserInfo> Info{ nullptr };//如若需要，应该在SetInfo中构建
};
#endif // CONTROL_USERINFOLSTITEM_H

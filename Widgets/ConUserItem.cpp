#include "ConUserItem.h"

#include <QLabel>

#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"

WConUserItem::WConUserItem(QWidget* parent):
	IListItemWgt(WgtFile::ContactUserItem,EListItemType::CONTACT_USER_ITEM,parent)
{
}

void WConUserItem::SetInfo(const QString& Name, const QString& Slogen, const QString& IconPath)
{
	Lab_BigName->setText(Name);
	Lab_UserSlogen->setText(Slogen);

	QPixmap Icon(IconPath);
	Lab_Icon->setPixmap(Icon.scaled(Lab_Icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	Lab_Icon->setScaledContents(true);
}

void WConUserItem::InitControls()
{
	Lab_BigName = UIHelper::AssertFindChild<QLabel*>(UI, "Lab_BigName");
	Lab_UserSlogen = UIHelper::AssertFindChild<QLabel*>(UI, "Lab_UserSlogen");
	Lab_Icon = UIHelper::AssertFindChild<QLabel*>(UI, "Lab_Icon");
}

void WConUserItem::ConnectSigSlot()
{
	IListItemWgt::ConnectSigSlot();
}

WConUserItem::~WConUserItem()
{
}

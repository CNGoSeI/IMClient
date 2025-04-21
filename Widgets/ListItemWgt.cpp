#include "ListItemWgt.h"

#include <QFile>
#include <QWidget>

IListItemWgt::IListItemWgt(const QString& UIRes, EListItemType InItemType, QWidget* parent):
	ILoadUIWgtBase(UIRes, parent),
	ItemType(InItemType)
{
	static auto GetUserItemQss = []()
		{
			QFile qssFile(":/Skin/UserItemWgt.qss");
			qssFile.open(QFile::ReadOnly);
			return qssFile.readAll();
		}();
	/*
	 * 该界面只是显示控件，样式交由listItem进行显示，背景透明
	 */
	UI->setStyleSheet(GetUserItemQss);
	UI->setAttribute(Qt::WA_TransparentForMouseEvents, true); // 鼠标事件穿透
	UI->setAttribute(Qt::WA_StyledBackground);
}

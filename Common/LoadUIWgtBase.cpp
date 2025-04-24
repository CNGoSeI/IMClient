#include "LoadUIWgtBase.h"

#include <QPainter>
#include <QWidget>
#include "Widgets/WidgetFilesHelper.h"

ILoadUIWgtBase::ILoadUIWgtBase(const QString& path, QWidget* parent):UI(WgtFile::LoadUI(path, parent))
{

}

ILoadUIWgtBase::~ILoadUIWgtBase()
{
	UI->deleteLater();
}

const QWidget* ILoadUIWgtBase::GetUI() const
{
	return UI;
}

QWidget* ILoadUIWgtBase::GetUI()
{
	return UI;
}

QRect ILoadUIWgtBase::GetTitleRect(int W, int H) const
{
	QPoint parentTopLeft = UI->mapToParent(QPoint(0, 0));
	return QRect(parentTopLeft.x(), parentTopLeft.y(), W, H);
}

void ILoadUIWgtBase::CreateWgt()
{
	Q_ASSERT(UI != nullptr, "ILoadUIWgtBase", "ILoadUIWgtBase::UI Load ERROR");
	UI->setProperty("_owner", QVariant::fromValue(this));  // 存储基类指针[6](@ref)
	InitControls();
	ConnectSigSlot();
}

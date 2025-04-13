#include "LoadUIWgtBase.h"
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

void ILoadUIWgtBase::CreateWgt()
{
	Q_ASSERT(UI != nullptr, "ILoadUIWgtBase", "ILoadUIWgtBase::UI Load ERROR");
	InitControls();
	ConnectSigSlot();
}

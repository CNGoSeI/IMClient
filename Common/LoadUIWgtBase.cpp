#include "LoadUIWgtBase.h"
#include <QWidget>
#include "Widgets/WidgetFilesHelper.h"

WLoadUIWgtBase::WLoadUIWgtBase(const QString& path, QWidget* parent):UI(WgtFile::LoadUI(path, parent))
{

}

WLoadUIWgtBase::~WLoadUIWgtBase()
{
}

const QWidget* WLoadUIWgtBase::GetUI() const
{
	return UI;
}

QWidget* WLoadUIWgtBase::GetUI()
{
	return UI;
}

void WLoadUIWgtBase::CreateWgt()
{
	Q_ASSERT(UI != nullptr, "WLoadUIWgtBase", "WLoadUIWgtBase::UI Load ERROR");
	InitControls();
	ConnectSigSlot();
}

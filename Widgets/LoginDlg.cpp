#include <QPushButton>
#include "LoginDlg.h"
#include "WidgetFilesHelper.h"

DLoginDialog::DLoginDialog(const QString& Path, QWidget* parent):WLoadUIWgtBase::WLoadUIWgtBase(Path, parent)
{
}

DLoginDialog::~DLoginDialog()
{
	UI->deleteLater();
}

void DLoginDialog::InitControls()
{
	Btn_Reg = UI->findChild<QPushButton*>("Btn_Reg");

	Q_ASSERT(Btn_Reg != nullptr);
}

void DLoginDialog::ConnectSigSlot()
{
	connect(Btn_Reg, &QPushButton::clicked, this, &DLoginDialog::sigSwitchRegister);
}

#include <QPushButton>
#include "LoginDlg.h"
#include "WidgetFilesHelper.h"

DLoginDialog::DLoginDialog(QWidget* parent):
WLoadUIWgtBase::WLoadUIWgtBase(WgtFile::LoginDlgPath, parent)
{
}

DLoginDialog::~DLoginDialog()
{
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

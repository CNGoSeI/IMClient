#ifndef LOGINDLG_H
#define LOGINDLG_H

#include "Common/LoadUIWgtBase.h"

class DLoginDialog : public WLoadUIWgtBase
{
    Q_OBJECT
public:
    explicit DLoginDialog(const QString& Path, QWidget* parent = nullptr);
    virtual ~DLoginDialog() override;

private:
    void InitControls() override;
    void ConnectSigSlot() override;
    class QPushButton* Btn_Reg;//×¢²á°´Å¥
signals:
    void sigSwitchRegister();//ÇÐ»»×¢²á
};

#endif
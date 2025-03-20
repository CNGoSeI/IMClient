#ifndef LOGINDLG_H
#define LOGINDLG_H

#include "Common/LoadUIWgtBase.h"

class DLoginDialog : public WLoadUIWgtBase
{
    Q_OBJECT
public:
    explicit DLoginDialog(QWidget* parent = nullptr);
    virtual ~DLoginDialog() override;

private:
    void InitControls() override;
    void ConnectSigSlot() override;
    class QPushButton* Btn_Reg;//´ò¿ª×¢²á°´Å¥
signals:
    void sigSwitchRegister();//ÇÐ»»×¢²á
};

#endif
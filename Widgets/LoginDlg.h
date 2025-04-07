#ifndef LOGINDLG_H
#define LOGINDLG_H

#include "Common/LoadUIWgtBase.h"

class QPushButton;
class QLineEdit;
class QLabel;

class DLoginDialog : public WLoadUIWgtBase
{
    Q_OBJECT
public:
    explicit DLoginDialog(QWidget* parent = nullptr);
    virtual ~DLoginDialog() override;
    void SetControlsToNormal() override;
private:
    void InitControls() override;
    void ConnectSigSlot() override;
    bool IsAllEdtInputMatch();
    void SetEditeLinesEnabale(bool bEnable = true);
    void SetEditeLinesToNormal();
    void InitHttpHandlers();//构建HTTP回调的键值对

private slots:
    void slotLoginFinish(const int ReqId, const QString& Res, const int ErrCode);

private:
    std::map<int, std::function<void(const QJsonObject&)>> Handlers;//ReqID对应执行操作

	QPushButton* Btn_Reg{nullptr};//打开注册按钮
    QPushButton* Btn_Login{ nullptr };
    QLabel* Lab_MsgTip{ nullptr };
    QLineEdit* Edt_User{ nullptr };
    QLineEdit* Edt_Passwd{ nullptr };
signals:
    void sigSwitchRegister();//切换注册
};

#endif
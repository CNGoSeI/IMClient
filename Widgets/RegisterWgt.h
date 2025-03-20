#ifndef REGISTERWGT_H
#define REGISTERWGT_H

#include "Common/LoadUIWgtBase.h"

class WRegisterWgt : public WLoadUIWgtBase
{
    Q_OBJECT
public:
    explicit WRegisterWgt(QWidget* parent = nullptr);
    virtual ~WRegisterWgt() override;

    void ShowErrTip(const QString& Tip);

public slots:
    /**
     * \brief 注册方法的请求返回
     * \param ReqID 
     * \param Res 
     * \param ErrCode 
     */
    void slotRegModFinish(const int ReqID, const QString& Res, const int ErrCode);
signals:
   void sigBtnOkClicked();

private:
    void InitControls() override;
    void ConnectSigSlot() override;
    class QPushButton* Btn_Ok{nullptr};//确认注册
    class QLineEdit* Edt_Password{ nullptr };//密码输入框
    class QLineEdit* Edt_Confirm{ nullptr };//确认密码
    class QLabel* Lab_ErrTip{ nullptr };
};

#endif
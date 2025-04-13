#ifndef REGISTERWGT_H
#define REGISTERWGT_H

#include "Common/LoadUIWgtBase.h"

class QLabel;
class QLineEdit;
class QPushButton;

class WRegisterWgt : public ILoadUIWgtBase
{
    Q_OBJECT
public:
    explicit WRegisterWgt(QWidget* parent = nullptr);
    virtual ~WRegisterWgt() override;

    //void ShowTip(const QString& Tip, bool b_ok);

public slots:
    /**
     * \brief 注册方法请求完成的请求返回
     * \param ReqID 
     * \param Res 
     * \param ErrCode 
     */
    void slotRegModFinish(const int ReqID, const QString& Res, const int ErrCode);

private slots:
    void slotRegister();//请求注册账号
signals:
   void sigBtnCancelClicked();
   //void sigRegSucessed();//注册成功

private:
    void InitControls() override;
    void ConnectSigSlot() override;
    void InitHttpHandlers();//构建HTTP回调的键值对
    void SetControlsToNormal() override;//将所有控件状态设为默认
    bool IsAllEdtInputMatch();//所有需要本地判断的输入框内容是否合规
    void SetRegControlEnable(const bool bEnable = true);//设置注册输入相关的控件是否启用

private:
    QPushButton* Btn_Ok{nullptr};//确认注册
    QLineEdit* Edt_Password{ nullptr };//密码输入框
    QLineEdit* Edt_Confirm{ nullptr };//确认密码
    QLabel* Lab_ErrTip{ nullptr };//请求返回信息提示
    QLineEdit* Edt_User{ nullptr };//用户名
    QLineEdit* Edt_Email{ nullptr };//邮箱
    QLineEdit* Edt_Verify{ nullptr };//验证码
    QPushButton* Btn_GetCode{ nullptr };//获取验证码

    std::map<int, std::function<void(const QJsonObject&)>> Handlers;//ReqID对应执行操作
};

#endif
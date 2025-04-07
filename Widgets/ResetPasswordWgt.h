#ifndef RESETPASSWORDWGT_H
#define RESETPASSWORDWGT_H
#include "Common/LoadUIWgtBase.h"

class QLabel;
class QLineEdit;
class QPushButton;

class WResetPasswordWgt : public WLoadUIWgtBase
{
    Q_OBJECT

public:
    explicit WResetPasswordWgt(QWidget* parent = nullptr);
    virtual ~WResetPasswordWgt() override=default;
    void SetControlsToNormal() override;    //设置各个控件显示回归默认
private:
    void InitControls() override;
    void ConnectSigSlot() override;
    void InitHttpHandlers();//初始化请求ID和对应的执行函数
    bool IsAllEdtInputMatch();//所有需要本地判断的输入框内容是否合规
    void SetEdtControlsState(const bool = false);//设置编辑框是否回归非错误提示状态
    void SetEdtControlsEnable(const bool bEnable);//部分编辑框需要在获取到验证码之后不再启用

private slots:
    /**
     * \brief 注册方法请求完成的请求返回
     * \param ReqID 返回的操作ID
     * \param Res 返回的数据
     * \param ErrCode 错误码
     */
    void slotRegModFinish(const int ReqID, const QString& Res, const int ErrCode);

private:
    QPushButton* Btn_Ok{ nullptr };//确认重置密码
    QLineEdit* Edt_Password{ nullptr };//密码输入框
    QLabel* Lab_MsgTip{ nullptr };//请求返回信息提示
    QLineEdit* Edt_User{ nullptr };//用户名
    QLineEdit* Edt_Email{ nullptr };//邮箱
    QLineEdit* Edt_Verify{ nullptr };//验证码
    QPushButton* Btn_GetCode{ nullptr };//获取验证码
    QPushButton* Btn_SwitchPwdShow{ nullptr };//切换显示密码栏

    std::map<int, std::function<void(const QJsonObject&)>> Handlers;//ReqID对应执行操作
};
#endif // RESETPASSWORDWGT_H

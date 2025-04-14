#ifndef GLOBALDEFINE_H
#define GLOBALDEFINE_H

#include <QWidget>
#include <QStyle>

class QLineEdit;
class QLabel;

namespace UIHelper
{
	extern void RePolish(class QWidget* TargetWgt);//刷新对象的QSS

	void SetTipState(QLabel* TipWgt,const QString& Tip,const bool bOk=true);//设置提示框文本和状态
	void SetLineEditError(QLineEdit* Target,bool IsError=false);//设置对象编辑框错误样式

	template <typename T>
	T AssertFindChild(QWidget* UI, const QString& ControlName)
	{
		if (!UI)return nullptr;
		T ControlP = UI->findChild<T>(ControlName);
		Q_ASSERT(ControlP);
		return ControlP;
	}
}

namespace Net
{
	const QString UrlBegin{ "http://" };//http 还是https
	const QString& UrlHome();
	const QString& NetPort();
	const QString& RequestMain();//请求地址如 http://a.a.a.a:pppp/

	const QString URI_GET_VERIFICATION{"/get_varifycode"};//获取验证码
	const QString URI_USER_REGISTER{ "/user_register" };//注册请求
	const QString URI_RESET_PWD{"/reset_pwd"};//重置密码
	const QString URI_USER_LOGIN{ "/user_login" };//登录

	struct ServerInfo {
		QString Host;
		QString Port;
		QString Token;
		int  Uid;
	};
}

namespace ReqID
{
	constexpr int ID_GET_VARIFY_CODE{ 1001 };//获取验证码
	constexpr int ID_REG_USER{ ID_GET_VARIFY_CODE+1 }; //注册用户
	constexpr int ID_RESET_PWD{ ID_GET_VARIFY_CODE+2 }; //重置密码
	constexpr int ID_LOGIN_USER{ ID_GET_VARIFY_CODE + 3 }; //登录
	constexpr int ID_CHAT_LOGIN{ ID_GET_VARIFY_CODE + 4 }; //连接聊天服务器
	constexpr int ID_CHAT_LOGIN_RSP{ ID_GET_VARIFY_CODE + 5}; //登陆聊天服务器回包
}

namespace ErrorCodes
{
	constexpr int SUCCESS{ 0 };
	constexpr int ERR_JSON{ 1 }; //Json解析失败
	constexpr int ERR_NETWORK{ 2 };

	constexpr int Send_Email_FAILD{ 550 };//发送验证码的邮箱不存在

	constexpr int Error_Json{ 1001 };//Json解析错误
	constexpr int RPCFailed{ Error_Json + 1 };//RPC请求错误
	constexpr int VarifyExpired{ Error_Json + 2 };//验证码无效
	constexpr int UserExist{ Error_Json + 3 };//用户已经存在
	constexpr int VarifyCodeErr{ Error_Json + 4 };//验证码不正确
	constexpr int EmailNotMatch{ Error_Json + 5 };//邮箱对不上
	constexpr int PasswdUpFailed{ Error_Json + 6 };//重制密码失败
	constexpr int PasswdInvalid{ Error_Json + 7 };//用户或密码错误
	constexpr int RPCGetFailed{ Error_Json + 8 };//获取Rpc失败
	const QString& GetErrorStr(const int);//获取错误码对应的错误提示

}

namespace Modules
{
	constexpr int REGISTERMOD{ 0 };//注册模式
	constexpr int RESETMOD{ 1 };//重设密码模式
	constexpr int LOGINMOD{ 2 };//登录模式
}

enum class EResizeArea {
	None, Left, Right, Top, Bottom,
	TopLeft, TopRight, BottomLeft, BottomRight
};


#endif
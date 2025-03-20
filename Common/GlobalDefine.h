#ifndef GLOBALDEFINE_H
#define GLOBALDEFINE_H

#include <QStyle>
#include <QWidget>

namespace UIHelper
{
	extern void RePolish(class QWidget* TargetWgt);//刷新对象的QSS
}

namespace Net
{
	/* 请求ID ReqID */
	constexpr int ID_GET_VARIFY_CODE{ 1001 };//获取验证码
	constexpr int ID_REG_USER{ 1002 }; //注册用户
	/* 请求ID ReqID */

	/* 错误代码 ErrorCodes */
	constexpr int SUCCESS{ 0 };
	constexpr int ERR_JSON{ 1 }; //Json解析失败
	constexpr int ERR_NETWORK{ 2 };
	/* 错误代码 ErrorCodes */

	/* 请求模式 Modules */
	constexpr int REGISTERMOD{ 0 };//注册模式
	/* 请求模式 Modules */
}


#endif
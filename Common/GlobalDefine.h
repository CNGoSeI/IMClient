﻿#ifndef GLOBALDEFINE_H
#define GLOBALDEFINE_H

#include <QWidget>
#include <QStyle>

namespace UIHelper
{
	extern void RePolish(class QWidget* TargetWgt);//刷新对象的QSS
}

namespace Net
{
	const QString UrlBegin{ "http://" };//http 还是https
	const QString& UrlHome();
	const QString& NetPort();
	const QString& RequestMain();//请求地址如 http://a.a.a.a:pppp/

	const QString URI_GET_VERIFICATION{"/get_varifycode"};//获取验证码
}

namespace ReqID
{
	constexpr int ID_GET_VARIFY_CODE{ 1001 };//获取验证码
	constexpr int ID_REG_USER{ 1002 }; //注册用户
}

namespace ErrorCodes
{
	constexpr int SUCCESS{ 0 };
	constexpr int ERR_JSON{ 1 }; //Json解析失败
	constexpr int ERR_NETWORK{ 2 };
}

namespace Modules
{
	constexpr int REGISTERMOD{ 0 };//注册模式
}


#endif
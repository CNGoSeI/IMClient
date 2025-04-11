#ifndef PUBLICFUN_H
#define PUBLICFUN_H
class QString;
class QJsonObject;
namespace Tool 
{
	bool IsStrMatchEmail(const QString& Email);

	QString EcryptionStr(const QString& Str);//对文本进行加密

	bool IsUserNameMatch(const QString& Str);//用户名是否合格

	bool IsPasswdMatch(const QString& Pwd);//密码是否合规

	bool ParserResponJson(const QString& Res, QJsonObject& OutJsonObj, const int ErrCode);
}
#endif // PUBLICFUN_H

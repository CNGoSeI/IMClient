#ifndef PUBLICFUN_H
#define PUBLICFUN_H
class QString;
class QJsonObject;
namespace Tool 
{
	bool IsStrMatchEmail(const QString& Email);

	QString EcryptionStr(const QString& Str);//���ı����м���

	bool IsUserNameMatch(const QString& Str);//�û����Ƿ�ϸ�

	bool IsPasswdMatch(const QString& Pwd);//�����Ƿ�Ϲ�

	bool ParserResponJson(const QString& Res, QJsonObject& OutJsonObj, const int ErrCode);
}
#endif // PUBLICFUN_H

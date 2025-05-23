﻿#include "PublicFun.h"
#include <qcryptographichash.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <qregularexpression.h>
#include "GlobalDefine.h"

bool Tool::IsStrMatchEmail(const QString& Email)
{
	QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
	return regex.match(Email).hasMatch(); // 执行正则表达式匹配
}

QString Tool::EcryptionStr(const QString& Str)
{
	QByteArray data = Str.toUtf8();
	QByteArray hash = QCryptographicHash::hash(data, QCryptographicHash::Sha256);
	return QString(hash.toHex());
}

bool Tool::IsUserNameMatch(const QString& Str)
{
    const auto Len = Str.length();
    return Len > 5 && Len < 13;
}

bool Tool::IsPasswdMatch(const QString& Pwd)
{
    // 规则1：至少8位
    if (Pwd.length() < 8) return false;

    // 规则3：不能为纯数字（优先验证）
    QRegularExpression pureNumber("^\\d+$");
    if (pureNumber.match(Pwd).hasMatch()) return false;

    // 规则2：必须包含大小写字母
    QRegularExpression pwdRule("^(?=.*[a-z])(?=.*[A-Z]).*$");
    return pwdRule.match(Pwd).hasMatch();
}

bool Tool::ParserResponJson(const QString& Res, QJsonObject& OutJsonObj, const int ErrCode)
{
	if (ErrCode != ErrorCodes::SUCCESS) {
		return false;
	}

	// 解析 JSON 字符串,res需转化为QByteArray
	QJsonDocument jsonDoc = QJsonDocument::fromJson(Res.toUtf8());

	//json解析错误
	if (jsonDoc.isNull()|| !jsonDoc.isObject()) {
	
		return false;
	}

	OutJsonObj = jsonDoc.object();
	return true;
}

#include "PublicFun.h"

#include <qregularexpression.h>

bool Tool::IsStrMatchEmail(const QString& Email)
{
	QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
	return regex.match(Email).hasMatch(); // 执行正则表达式匹配
}

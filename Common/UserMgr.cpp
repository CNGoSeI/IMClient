#include "UserMgr.h"

void SUserMgr::SetName(const QString& name)
{
	Name = name;
}

void SUserMgr::SetUid(int uid)
{
	UId = uid;
}

void SUserMgr::SetToken(const QString& token)
{
	Token = token;
}

#ifndef USERMGR_H
#define USERMGR_H

#include <QObject>

#include "SingletonTemplate.h"

class SUserMgr:public QObject,public TSingleton<SUserMgr>
{
    Q_OBJECT
public:
    friend class TSingleton<SUserMgr>;
    ~SUserMgr()=default;
    void SetName(const QString& name);
    void SetUid(int uid);
    void SetToken(const QString& token);

    const QString& GetName() const { return Name; };
    int GetUid() const { return UId; };
    const QString& GetToken() const { return Token; };
private:
    SUserMgr()=default;
    QString Name;
    QString Token;
    int UId;
};
#endif // USERMGR_H

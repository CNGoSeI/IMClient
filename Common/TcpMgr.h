#ifndef TCPMGR_H
#define TCPMGR_H
#include <QObject>
#include <qtcpsocket.h>

#include "SingletonTemplate.h"

namespace Infos
{
	struct FAddFriendApply;
}

namespace Infos
{
	struct FSearchInfo;
}

namespace Net
{
	struct ServerInfo;
}

class STcpMgr:public QObject,public TSingleton<STcpMgr>
{
    Q_OBJECT
	friend TSingleton<STcpMgr>;
    using CallbackFunType=std::function<void(int,int,QByteArray&)>;
public slots:
    void slotTcpConnect(const Net::ServerInfo&);
private slots:
    void slotSendData(int reqId, const QByteArray& data);
    void slotReadReceived();//读取收到的buff
    void slotGetConnectError(const QTcpSocket::SocketError& socketError);//该错误为QT套接字回调调用
signals:
    void sigConSuccess(bool bSuccess);//该错误为QT套接字连接中错误回调转发的信号
    void sigSendData(int reqId, const QByteArray& data);
    void sigLoginFailed(int);//登录请求回调的错误
    void sigSwitchChatWgt();
    void sigUserSearch(const Infos::FSearchInfo& info);
    void sigFriendApply(const Infos::FAddFriendApply&);//提示好友申请通知
private:
    STcpMgr();

    void InitHandlers();
    void HandleMsg(int ReqId, int len, QByteArray& data);

    /**
     * 收到数据之后解析包，判断有无错误，并且设置json
     * @param data 解析的数据包
     * @param JsonObj 要设置的json
     * @return 
     */
    bool PaserBaseDate(int Id, const QByteArray& data, QJsonObject& JsonObj);

private:
    QTcpSocket Socket;
    QString Host{""};
    uint16_t Port{0};
    QByteArray Buffer;
    bool bRecvPending{false};//标识是否读取了数据包头，每次读取了完整的包后应该置为假
    quint16 MessageId{0};
    quint16 MessageLen{0};
    std::map<int, CallbackFunType> ReqId2Callback;

};
#endif // TCPMGR_H

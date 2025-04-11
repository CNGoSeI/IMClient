#ifndef TCPMGR_H
#define TCPMGR_H
#include <QObject>
#include <qtcpsocket.h>

#include "SingletonTemplate.h"

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
    void slotSendData(int reqId, const QString& data);
    void slotReadReceived();//读取收到的buff
    void slotGetConnectError(const QTcpSocket::SocketError& socketError);//该错误为QT套接字回调调用
signals:
    void sigConSuccess(bool bSuccess);//该错误为QT套接字连接中错误回调转发的信号
    void sigSendData(int reqId, const QString& data);
    void sigLoginFailed(int);//登录请求回调的错误
    void sigSwitchChatWgt();
private:
    STcpMgr();

    void InitHandlers();
    void HandleMsg(int ReqId, int len, QByteArray& data);

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

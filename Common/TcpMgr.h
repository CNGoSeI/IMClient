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
	
public slots:
    void slotTcpConnect(const Net::ServerInfo&);
private slots:
    void slotSendData(int reqId, const QString& data);
    void slotReadReceived();//读取收到的buff
    void slotGetConnectError(const QTcpSocket::SocketError& socketError);
signals:
    void sigConSuccess(bool bSuccess);
    void sigSendData(int reqId, const QString& data);
private:
    STcpMgr();

private:
    QTcpSocket Socket;
    QString Host{""};
    uint16_t Port{0};
    QByteArray Buffer;
    bool bRecvPending{false};//标识是否读取了数据包头，每次读取了完整的包后应该置为假
    quint16 MessageId{0};
    quint16 MessageLen{0};

};
#endif // TCPMGR_H

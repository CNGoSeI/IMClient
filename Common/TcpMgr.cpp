#include "TcpMgr.h"

#include <qdatastream.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "GlobalDefine.h"
#include "UserMgr.h"
#include "Widgets/LoadingWgt.h"

STcpMgr::STcpMgr()
{
	QObject::connect(&Socket, &QTcpSocket::connected, [this]()
	{
		qDebug() << "成功连接到服务!";
		// 连接建立后发送消息
		emit sigConSuccess(true);
	});

	// 当有数据可读时，读取所有数据
	QObject::connect(&Socket, &QTcpSocket::readyRead, this,&STcpMgr::slotReadReceived);

	// 处理连接断开
	QObject::connect(&Socket, &QTcpSocket::disconnected, [this]()
	{
		qDebug() << "从服务器断开链接.";
	});

	QObject::connect(this, &STcpMgr::sigSendData, this, &STcpMgr::slotSendData);

	QObject::connect(&Socket, static_cast<void (QTcpSocket::*)(QTcpSocket::SocketError)>(&QTcpSocket::error), this,
	                 &STcpMgr::slotGetConnectError);

	InitHandlers();
}

void STcpMgr::InitHandlers()
{
	ReqId2Callback.emplace(ReqID::ID_CHAT_LOGIN_RSP, [this](int Id, int Len, QByteArray& Data)
	{
			QJsonObject jsonObj;
			bool Succes=PaserBaseDate(Id,Data, jsonObj);
			if (!Succes)return;

			SUserMgr::GetInstance().SetUid(jsonObj["uid"].toInt());
			SUserMgr::GetInstance().SetName(jsonObj["name"].toString());
			SUserMgr::GetInstance().SetToken(jsonObj["token"].toString());

			SUserMgr::GetInstance().SetToken(jsonObj["token"].toString());

			qDebug("于登录聊天室获取回复时 登陆成功,uid: %d Name %s Token: %s",
			       SUserMgr::GetInstance().GetUid(),
			       SUserMgr::GetInstance().GetName().toUtf8().data(),
			       SUserMgr::GetInstance().GetToken().toUtf8().data());

			emit sigSwitchChatWgt();

			//好友申请列表
			if (jsonObj.contains("apply_list")) {
				SUserMgr::GetInstance().AppendApplyList(jsonObj["apply_list"].toArray());
			}

			//添加好友列表
			if (jsonObj.contains("friend_list")) {
				SUserMgr::GetInstance().AppendFriendList(jsonObj["friend_list"].toArray());
			}
	});

	ReqId2Callback.emplace(ReqID::ID_SEARCH_USER_RSP, [this](int Id, int Len, QByteArray& Data)
	{
		//收到服务器发包之后关闭模态
		SLoadingWgt::Instance().HideStop();

		QJsonObject jsonObj;
		bool Succes = PaserBaseDate(Id, Data, jsonObj);
		if (!Succes)return;

		Infos::FSearchInfo search_info;
		search_info.UID = jsonObj["uid"].toInt();
		search_info.Name = jsonObj["name"].toString();
		search_info.Nick = jsonObj["nick"].toString();
		search_info.Desc = jsonObj["desc"].toString();
		search_info.Sex = jsonObj["sex"].toInt();
		search_info.Icon = jsonObj["icon"].toString();

		emit sigUserSearch(search_info);

	});

	ReqId2Callback.emplace(ReqID::ID_NOTIFY_ADD_FRIEND_REQ, [this](int Id, int Len, QByteArray& Data)
	{
		QJsonObject jsonObj;
		bool Succes = PaserBaseDate(Id, Data, jsonObj);
		if (!Succes)return;

		Infos::FAddFriendApply apply_info;
		apply_info.FromUid = jsonObj["applyuid"].toInt();
		apply_info.Name = jsonObj["name"].toString();
		apply_info.Desc = jsonObj["desc"].toString();
		apply_info.Icon = jsonObj["icon"].toString();
		apply_info.Nick = jsonObj["nick"].toString();
		apply_info.Sex = jsonObj["sex"].toInt();

		emit sigFriendApply(apply_info,true);
	});

	ReqId2Callback.emplace(ReqID::ID_AUTH_FRIEND_RSP, [this](int Id, int Len, QByteArray& Data)
	{
		QJsonObject jsonObj;
		bool Succes = PaserBaseDate(Id, Data, jsonObj);
		if (!Succes)return;

		auto name = jsonObj["name"].toString();
		auto nick = jsonObj["nick"].toString();
		auto icon = jsonObj["icon"].toString();
		auto sex = jsonObj["sex"].toInt();
		auto uid = jsonObj["uid"].toInt();
		Infos::BaseUserInfo BaseInfo(uid, name, icon);
		BaseInfo.Sex = sex;
		SUserMgr::GetInstance().AddFriend(BaseInfo);
		emit sigAuthRsp(BaseInfo);
	});

	ReqId2Callback.emplace(ReqID::ID_NOTIFY_AUTH_FRIEND_REQ, [this](int Id, int Len, QByteArray& Data)
		{
			QJsonObject jsonObj;
			bool Succes = PaserBaseDate(Id, Data, jsonObj);
			if (!Succes)return;

			int from_uid = jsonObj["fromuid"].toInt();//对方的id
			QString name = jsonObj["name"].toString();
			QString nick = jsonObj["nick"].toString();
			QString icon = jsonObj["icon"].toString();
			int sex = jsonObj["sex"].toInt();

			Infos::BaseUserInfo BaseInfo(from_uid, name, icon);
			BaseInfo.Sex = sex;
			BaseInfo.Desc = nick;
			SUserMgr::GetInstance().AddFriend(BaseInfo);
			emit sigAddAuthFriend(BaseInfo);
		});
}

void STcpMgr::HandleMsg(int ReqId, int len, QByteArray& data)
{
	auto find_iter = ReqId2Callback.find(ReqId);
	if (find_iter == ReqId2Callback.end()) {
		qDebug() << "Tcp回调未找到 [" << ReqId << "] ";
		return;
	}

	find_iter->second(ReqId, len, data);
}

bool STcpMgr::PaserBaseDate(int Id, const QByteArray& data, QJsonObject& JsonObj)
{
	qDebug() << "回调ID：" << Id << " 数据：" << data;

	// 将QByteArray转换为QJsonDocument
	QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

	// 检查转换是否成功
	if (jsonDoc.isNull()) {
		qDebug() << "QJsonDocument 转换异常 于登录聊天室获取回复时.";
		return false;
	}

	JsonObj = jsonDoc.object();

	if (!JsonObj.contains("error")) {
		int err = ErrorCodes::ERR_JSON;
		qDebug() << "Json解析异常" << err;
		emit sigLoginFailed(err);
		return false;
	}

	int err = JsonObj["error"].toInt();
	if (err != ErrorCodes::SUCCESS) {
		qDebug() << "请求不成功" << err;
		emit sigLoginFailed(err);
		return false;
	}
	return true;
}

void STcpMgr::slotTcpConnect(const Net::ServerInfo& si)
{
	// 尝试连接到服务器

	Host = si.Host;
	Port = static_cast<uint16_t>(si.Port.toUInt());
	qDebug() << "链接服务器..." << "host: " << Host<<" Port: "<<Port;
	Socket.connectToHost(si.Host, Port);
}

void STcpMgr::slotSendData(int reqId, const QByteArray& data)
{
	uint16_t id = reqId;
	quint16 len = static_cast<quint16>(data.size());// 计算长度（使用网络字节序转换）

	// 创建一个QByteArray用于存储要发送的所有数据
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);

	out.setByteOrder(QDataStream::BigEndian);// 设置数据流使用网络字节序
	out << id << len;// 写入ID和长度为头
	block.append(data);// 再添加字符串数据

	// 发送数据
	Socket.write(block);
}

void STcpMgr::slotReadReceived()
{
	/**
	 * TCP没有数据边界，按流传输，因此存在粘包现象，读取buff需要：
	 *	- Buff至少能够解析出包头，不然直接返回。等待下一次收到的数据，进行追加拼接
	 *	- Buff能够解析出ID、和消息体大小的时候，将包头去掉，并且读取消息大小的数据
	 *		* 如果Buff剩下的大小没有解析的消息体大小大，说明这一轮的数据不完全，直接返回，拼接下一轮数据
	 *	- 成功解析完一个包之后，将BUFF的首个位置裁剪到本轮解析完的包体之后，重新开始准备解析下一个包
	 */

	// 读取所有数据并追加到缓冲区
	Buffer.append(Socket.readAll());

	QDataStream stream(&Buffer, QIODevice::ReadOnly);
	stream.setVersion(QDataStream::Qt_5_0);

	forever
	{
		//未读取头部先解析头部
		if (!bRecvPending)
		{
			// 检查缓冲区中的数据是否足够解析出一个消息头（消息ID + 消息长度）
			if (Buffer.size() < static_cast<int>(sizeof(quint16) * 2))
			{
				return; // 数据不够，等待更多数据
			}

			stream >> MessageId >> MessageLen;// 预读取消息ID和消息长度，但不从缓冲区中移除
			qDebug() << "Message ID:" << MessageId << ", Length:" << MessageLen;

			Buffer = Buffer.mid(sizeof(quint16) * 2);//将buffer中的前四个字节移除(id和len)
			
		}

		//buffer剩余长读是否满足消息体长度，不满足则退出继续等待接受
		if (Buffer.size() < MessageLen)
		{
			bRecvPending = true;//已经读取过包头了
			return;
		}

		bRecvPending = false;//到这里相当于已经读取了完整的一个包，因此置为假

		QByteArray messageBody = Buffer.mid(0, MessageLen);// 从第0个开始读n个字节，相当于去头的消息体
		qDebug() << "收到的信息本体为： " << messageBody;

		Buffer = Buffer.mid(MessageLen);//到第n字节之后,这里相当于移到了一个完整的包之后

		HandleMsg(MessageId, MessageLen, messageBody);//触发回调
	}
}

void STcpMgr::slotGetConnectError(const QTcpSocket::SocketError& socketError)
{
	qDebug() << "套接字出现错误: " << Socket.errorString();
	switch (socketError)
	{
	case QTcpSocket::ConnectionRefusedError:
		qDebug() << "拒绝连接!";
		emit sigConSuccess(false);
		break;
	case QTcpSocket::RemoteHostClosedError:
		qDebug() << "远程主机关闭连接!";
		break;
	case QTcpSocket::HostNotFoundError:
		qDebug() << "未找到主机!";
		emit sigConSuccess(false);
		break;
	case QTcpSocket::SocketTimeoutError:
		qDebug() << "连接超时!";
		emit sigConSuccess(false);
		break;
	case QTcpSocket::NetworkError:
		qDebug() << "网络错误!";
		break;
	default:
		qDebug() << "其他错误!";
		break;
	}
}

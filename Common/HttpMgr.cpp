#include "HttpMgr.h"
#include <QString>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkRequest> 
#include <QNetworkReply>
#include "GlobalDefine.h"

SHttpMgr::SHttpMgr()
{
	//连接http请求和完成信号，信号槽机制保证队列消费
	connect(this, &SHttpMgr::sigHttpFinish, this, &SHttpMgr::slotHttpFinish);
}

SHttpMgr::~SHttpMgr()
{
}

void SHttpMgr::PostHttpReq(const QUrl& url, const QJsonObject& Json, const int ReqID, const int Mod)
{
	auto Data = QJsonDocument(Json).toJson();

	//从url创建请求
	QNetworkRequest Request(url);
	/**
	 * HTTP 基于TCP的短链接 为了断开连接不丢包粘包需要添加头来表识
	 */
	Request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");//表示JSon
	Request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(Data.length()));//表示包大小

	QNetworkReply* Reply = Managger.post(Request, Data);

	QObject::connect(Reply, &QNetworkReply::finished, [ReqID, Mod, Reply,this]()
	{
			//处理错误的情况
			if (Reply->error() != QNetworkReply::NoError) {
				qDebug() << Reply->errorString();
				//发送信号通知完成
				emit this->sigHttpFinish(ReqID, "", ErrorCodes::ERR_NETWORK, Mod);
				Reply->deleteLater();
				return;
			}
	
			//无错误则读回请求
			QString res = Reply->readAll();
	
			//发送信号通知完成
			emit this->sigHttpFinish(ReqID, res, ErrorCodes::SUCCESS, Mod);
			Reply->deleteLater();
			return;
	});
}

void SHttpMgr::slotHttpFinish(const int ReqId, const QString& Res, const int ErrorCode, const int Mod)
{
	if (Mod == Modules::REGISTERMOD)
	{
		emit sigRegModFinish(ReqId, Res, ErrorCode);
	}
}

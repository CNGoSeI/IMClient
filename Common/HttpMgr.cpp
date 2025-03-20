#include "HttpMgr.h"
#include <QString>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkRequest> 
#include <QNetworkReply>

SHttpMgr::SHttpMgr()
{
	//连接http请求和完成信号，信号槽机制保证队列消费
	connect(this, &HttpMgr::sigHttpFinish, this, &HttpMgr::slotHttpFinish);
}

SHttpMgr::~SHttpMgr()
{
}

void SHttpMgr::PostHttpReq(const QUrl& url, const QJsonObject& Json, const int ReqID, const int Mod)
{
	auto Data = QJsonDocument(Json).toJson();

	//从url创建请求
	QNetworkRequest Request(url);
	Request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	Request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(Data.length()));

	QNetworkReply* Reply = _manager.post(Request, Data);

	//QObject::connect(Reply, &QNetworkReply::finished, [ReqID, Mod, Reply,this]()
	//{
	//		//处理错误的情况
	//		if (Reply->error() != QNetworkReply::NoError) {
	//			qDebug() << Reply->errorString();
	//			//发送信号通知完成
	//			emit this->sigHttpFinish(ReqID, "", ErrorCodes::ERR_NETWORK, Mod);
	//			Reply->deleteLater();
	//			return;
	//		}
	//
	//		//无错误则读回请求
	//		QString res = Reply->readAll();
	//
	//		//发送信号通知完成
	//		emit this->sigHttpFinish(ReqID, res, ErrorCodes::SUCCESS, Mod);
	//		Reply->deleteLater();
	//		return;
	//});
}

void SHttpMgr::slotHttpFinish(const int ReqId, const QString& Res, const int ErrorCode, const int Mod)
{
	if (Mod == Net::REGISTERMOD)
	{
		emit sigRegModFinish(ReqId, Res, ErrorCode);
	}
}

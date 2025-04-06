#ifndef HTTPMGR_H
#define HTTPMGR_H
#include <QObject>
#include <QNetworkAccessManager>
#include "SingletonTemplate.h"

class SHttpMgr:public QObject,public TSingleton<SHttpMgr>
{
	Q_OBJECT
public:
	~SHttpMgr() override;

	/**
	* 投递HTTP请求
	* @url: 请求地址
	* @Json: 请求数据
	* @ReqID: 请求的代码，见GlobalDefine中的Net::ReqID
	* @Mod: 请求的模式，见GlobalDefine中的Net::Mod
	*/
	void PostHttpReq(const class QUrl& url, const class QJsonObject& Json, const int ReqID, const int Mod);
public slots:
	/**
	* Http接到请求之后 会发送sig，sig链接了该slot。如蜜传如蜜了
	* 该方法将请求完成的回调根据请求类型分发
	* @Mod 请求方法类型
	*/
	void slotHttpFinish(const int ReqId, const QString& Res, const int ErrorCode , const int Mod);
signals:
	/**
	* QT信号 完成HTTP请求之后发送
	* @ReqId 见GlobalDefine中的Net::ReqID
	* @ErrCode 见GlobalDefine中的Net::ErrCode
	*/
	void sigHttpFinish(const int ReqId, const QString& Res, const int ErrCode, const int Mod);

	/**
	* QT信号 HTTP注册请求返回后转发MOD相关的处理
	*/
	void sigRegModFinish(const int ReqId, const QString& Res, const int ErrCode);

	/**
	 * QT信号 HTTP重置密码请求返回后转发MOD相关的处理
	 */
	void sigResetPwdModFinish(const int ReqId, const QString& Res, const int ErrCode);
private:
	friend class TSingleton<SHttpMgr>;
	SHttpMgr();

	QNetworkAccessManager Managger;

};

#endif // !HTTPMGR_H
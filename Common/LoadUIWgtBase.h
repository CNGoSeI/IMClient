#ifndef LOADUIWGTBASE_H
#define LOADUIWGTBASE_H
#include<QObject>

class WLoadUIWgtBase :public QObject
{
	Q_OBJECT
public:
	WLoadUIWgtBase(const QString& paht, QWidget* parent = nullptr);
	virtual ~WLoadUIWgtBase();
	void CreateWgt();//调用这个创建UI
	const QWidget* GetUI()const;
	QWidget* GetUI();

protected:
	virtual void InitControls()=0;
	virtual void ConnectSigSlot(){};

	QWidget* UI{ nullptr };
};


#endif

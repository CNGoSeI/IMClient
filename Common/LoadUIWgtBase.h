#ifndef LOADUIWGTBASE_H
#define LOADUIWGTBASE_H
#include<QObject>

class ILoadUIWgtBase :public QObject
{
	Q_OBJECT
public:
	ILoadUIWgtBase(const QString& paht, QWidget* parent = nullptr);
	virtual ~ILoadUIWgtBase();
	void CreateWgt();//调用这个创建UI
	const QWidget* GetUI()const;
	QWidget* GetUI();

protected:
	virtual void InitControls()=0;
	virtual void ConnectSigSlot(){};
	virtual void SetControlsToNormal() {};//设置控件们回归普通状态

	QWidget* UI{ nullptr };
};


#endif

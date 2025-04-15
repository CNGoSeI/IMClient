#ifndef LOADUIWGTBASE_H
#define LOADUIWGTBASE_H
#include<QObject>

class QRect;
class ILoadUIWgtBase :public QObject
{
	Q_OBJECT
public:
	ILoadUIWgtBase(const QString& paht, QWidget* parent = nullptr);
	virtual ~ILoadUIWgtBase();
	void CreateWgt();//调用这个创建UI
	const QWidget* GetUI()const;
	QWidget* GetUI();

	//返回此时界面从0,0开始宽W高H的Rect区域
	QRect GetTitleRect(int W, int H) const;

protected:
	virtual void InitControls()=0;
	virtual void ConnectSigSlot(){};
	virtual void SetControlsToNormal() {};//设置控件们回归普通状态

	bool bMouseInTitle{ false };//光标在标题栏中？
	QWidget* UI{ nullptr };
};


#endif

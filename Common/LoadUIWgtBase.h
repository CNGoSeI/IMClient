#ifndef LOADUIWGTBASE_H
#define LOADUIWGTBASE_H
#include <QWidget>

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

	//返回UI的ILoadUIWgtBase对象
	//template <typename T>
	//static T* GetOwner(QWidget* Target)
	//{
	//	// 类型安全校验
	//	static_assert(std::is_base_of_v<ILoadUIWgtBase, T>,
	//	              "T 必须为 ILoadUIWgtBase 后代");
	//	static_assert(std::is_base_of_v<QObject, T>,
	//	              "T 必须为 QObject 后代");
	//	if (!Target) return nullptr;
	//
	//	// 从动态属性获取基类指针
	//	QVariant var = Target->property("_owner");
	//	if (!var.isValid()) return nullptr;
	//
	//	// 双重安全转换
	//	QObject* baseObj = qvariant_cast<QObject*>(var);
	//	if (!baseObj) return nullptr;
	//
	//	// Qt安全向下转型
	//	return qobject_cast<T*>(baseObj);
	//}

protected:
	virtual void InitControls()=0;
	virtual void ConnectSigSlot(){};
	virtual void SetControlsToNormal() {};//设置控件们回归普通状态

	bool bMouseInTitle{ false };//光标在标题栏中？
	QWidget* UI{ nullptr };
};


#endif

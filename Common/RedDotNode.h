#ifndef COMMON_REDDOTNODE_H
#define COMMON_REDDOTNODE_H
#include <functional>
#include <list>
#include <map>
#include <string>

using FShowFunc=std::function<void(bool bShow)>;
class CRedDotNode
{
	friend class SRedDotMgr;
public:
	virtual ~CRedDotNode();
	const std::string& GetTotalName() const { return TotalName; };
	const std::string& GetNodeName() const { return NodeName; };
	void DeleteChild(CRedDotNode* Child);
	void NotifyShow(bool bNeedShow);

	/*
	 * 可能存在先创建父节点补位的情况下，函数未设置
	 */
	void SetShowEvent(FShowFunc Func) { ShowEvent = std::move(Func); };
private:
	CRedDotNode(const std::string& TotalNodeName, FShowFunc NotifyFunc);
	void InitNodeName();
	void UpdateParentCounter(int delta);
	void UpdateDisplayState(bool bNewState, bool bTriggerEvent);

	std::string TotalName;//该红点全节点名称
	std::string NodeName;//该红点最右节点名称
	std::string ParentTotalName;//父红点全名
	CRedDotNode* ParentNode{ nullptr };
	bool bShow{ false };//是否处于显示状态
	std::list<CRedDotNode*> Children;
	int ChildrenShowCount{ 0 };//存在多少个直接子节点还在显示
	FShowFunc ShowEvent;//显示状态变化时，调用此函数通知界面切换显示状态
};

/* 红点管理 */
class SRedDotMgr
{
private:
	SRedDotMgr() = default;
	SRedDotMgr(const SRedDotMgr&) = delete;
	SRedDotMgr& operator=(const SRedDotMgr&) = delete;

public:
	static SRedDotMgr& Ins();
	CRedDotNode* FindTarget(CRedDotNode* Target);
	CRedDotNode* FindTargetByTotalName(const std::string& TargetName);
	bool NotifyTargetShow(bool bShow, CRedDotNode* Target);
	CRedDotNode* CreateNode(const std::string& name, FShowFunc func);

	std::list<CRedDotNode*> TotalNodes;
};

#endif // COMMON_REDDOTNODE_H

#ifndef COMMON_REDDOTNODE_H
#define COMMON_REDDOTNODE_H

/************************************************
 *				树状红点通知系统					*
 *	按 父节点.子节点.孙节点的新师做树状分割		*
 ************************************************/

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

	/**
	 * 此函数会改变节点显示状态和父节点的子节点显示的数量
	 * 相应显示控件显示切换也只应该由该函数管理
	 * 是否切换显示由当前显示状态和现存的字节的显示数量影响
	 * @param bNeedShow 是否显示
	 */
	void NotifyShow(bool bNeedShow);

	/*
	 * 可能存在先创建父节点补位的情况下，函数未设置
	 */
	void SetShowEvent(FShowFunc Func) { ShowEvent = std::move(Func); };
private:
	CRedDotNode(const std::string& TotalNodeName, FShowFunc NotifyFunc);//由mgr创建
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
	bool NotifyTargetShow(bool bShow, const std::string& TotalName);//通过节点名称通知红点

	/**
	 * 创建一个新的节点，如果节点已经存在，则设置新的显示回调函数
	 * @param name 节点全名称
	 * @param func 节点状态改变时，调用的回调
	 * @return 
	 */
	CRedDotNode* CreateNode(const std::string& name, FShowFunc func);

	std::list<CRedDotNode*> TotalNodes;
};

#endif // COMMON_REDDOTNODE_H

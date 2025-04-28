#include "RedDotNode.h"

#include <utility>

CRedDotNode::CRedDotNode(const std::string& TotalNodeName, FShowFunc NotifyFunc) :
	TotalName(TotalNodeName),
	ShowEvent(std::move(NotifyFunc))
{
	InitNodeName();

}

CRedDotNode::~CRedDotNode()
{
	SRedDotMgr::Ins().TotalNodes.remove_if([this](const auto& Target)
	{
		return this == Target;
	});

	if (ParentNode)
	{
		ParentNode->DeleteChild(this);
		ParentNode = nullptr;
	}
}

void CRedDotNode::DeleteChild(CRedDotNode* Child)
{
	auto it = Children.remove_if([&Child](const auto& Target)
	{
		return Child == Target;
	});
}

void CRedDotNode::NotifyShow(bool bNeedShow)
{
	const bool bStateChanged = (bShow != bNeedShow);

	if (bNeedShow)
	{
		//如果反复调用，但是状态未变，则计数不改变
		UpdateParentCounter(bStateChanged ? +1 : 0);
		UpdateDisplayState(true, bStateChanged);
		return;
	}
	/* 隐藏逻辑仅在没有子节点显示的情况下进行 */
	else if (ChildrenShowCount < 1)
	{
		ChildrenShowCount = 0;
		UpdateParentCounter(bStateChanged ? -1 : 0);
		UpdateDisplayState(false, bStateChanged);
	}
}

/* 处理父节点计数更新和递归调用 */
void CRedDotNode::UpdateParentCounter(int delta)
{
	if (!ParentNode || delta == 0) return;

	ParentNode->ChildrenShowCount += delta;
	ParentNode->NotifyShow(delta > 0);
}

// 统一更新显示状态和事件触发
void CRedDotNode::UpdateDisplayState(bool bNewState, bool bTriggerEvent)
{
	if (bTriggerEvent) {
		ShowEvent(bNewState);
	}
	bShow = bNewState;
}

void CRedDotNode::InitNodeName()
{
	// 查找最后一个点号的位置
	size_t dotPos = TotalName.rfind('.');

	if (dotPos != std::string::npos && dotPos < TotalName.length() - 1)
	{
		// 截取点号后的子字符串
		NodeName = TotalName.substr(dotPos + 1);
		ParentTotalName = TotalName.substr(0, dotPos - 1);

		//设置父项
		if (!ParentTotalName.empty())
		{
			ParentNode = SRedDotMgr::Ins().CreateNode(ParentTotalName, [](bool) {});
		}
	}
	else
	{
		// 直接使用完整字符串
		NodeName = TotalName;
	}
}

SRedDotMgr& SRedDotMgr::Ins()
{
	static SRedDotMgr Ins;
	return Ins;
}

CRedDotNode* SRedDotMgr::FindTarget(CRedDotNode* Target)
{
	for (auto it : SRedDotMgr::Ins().TotalNodes)
	{
		if (it == Target)
		{
			return Target;
		}
	}
	return nullptr;
}

CRedDotNode* SRedDotMgr::FindTargetByTotalName(const std::string& TargetName)
{
	for (auto it : SRedDotMgr::Ins().TotalNodes)
	{
		if (it->GetTotalName() == TargetName)
		{
			return it;
		}
	}
	return nullptr;
}

bool SRedDotMgr::NotifyTargetShow(bool bShow, CRedDotNode* Target)
{
	if(auto pNode=FindTarget(Target))
	{
		pNode->NotifyShow(bShow);
		return true;
	}

	return false;
}

CRedDotNode* SRedDotMgr::CreateNode(const std::string& name, FShowFunc func)
{
	if (auto exist = FindTargetByTotalName(name))
	{
		exist->SetShowEvent(std::move(func)); // 更新已有节点
		return exist; // 返回已有节点
	}

	auto newNode = new CRedDotNode(name, std::move(func));
	TotalNodes.emplace_back(newNode);
	return newNode; // 新建节点
}

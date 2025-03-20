#include "GlobalDefine.h"

void UIHelper::RePolish(QWidget* TargetWgt) {
    //取消style状态之后再填入状态
    TargetWgt->style()->unpolish(TargetWgt);
    TargetWgt->style()->polish(TargetWgt);
};
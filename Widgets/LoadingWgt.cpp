#include "LoadingWgt.h"

#include <QMovie>
#include <QLabel>
#include <QDialog>
#include <QBitmap>
#include <QPainter>

#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"

SLoadingWgt::SLoadingWgt() :
	ILoadUIWgtBase(WgtFile::LoadingWgt, nullptr)
{
	UI->setObjectName("Wgt_Loading");
}

SLoadingWgt& SLoadingWgt::Instance()
{
	static SLoadingWgt Ins;
	static bool bFirst{ true };

	if (bFirst)
	{
		Ins.CreateWgt();
		bFirst = false;
	}

	return Ins;
}

void SLoadingWgt::PopShow(QWidget* Parent)
{
	//Dlg->setParent(Parent);
	
	UI->setFixedSize(Parent->size());
	UI->move(Parent->pos());

	if (Movie)Movie->start();

	/*
	 * 如果想要该UI遮罩贴合目标，那么UI文件的顶层Widget的各Margin应该一致
	 * 细节margin由子控件设置吧
	 */
	UI->show();
}

void SLoadingWgt::HideStop()
{
	UI->close();
	if (Movie)Movie->stop();
}

void SLoadingWgt::InitControls()
{
	Lab_Moive = UIHelper::AssertFindChild<QLabel*>(UI, "Lab_Moive");

	Movie = new QMovie(":/Skin/Image/loading.gif"); // 加载动画的资源文件
	Lab_Moive->setMovie(Movie);
	Lab_Moive->setScaledContents(true);

	UI->setAttribute(Qt::WA_TranslucentBackground);
	UI->setAttribute(Qt::WA_StyledBackground);
	UI->setWindowFlags(UI->windowFlags() | Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	UI->setWindowModality(Qt::ApplicationModal);
	UIHelper::RePolish(UI);
}


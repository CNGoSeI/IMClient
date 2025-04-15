#include "CloseTitleWgt.h"

#include <QApplication>
#include <QPushButton>
#include <QMessageBox>

#include "mainwindow.h"
#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"

WCloseTitle::WCloseTitle(QWidget* parent):
 ILoadUIWgtBase(WgtFile::CloseTitle,parent)
{
	FollowedWgt = parent;
}

WCloseTitle::~WCloseTitle()
{
}

void WCloseTitle::InitControls()
{
	Btn_Max = UIHelper::AssertFindChild<QPushButton*>(UI, "Btn_Max");
	Btn_Min = UIHelper::AssertFindChild<QPushButton*>(UI, "Btn_Min");
	Btn_Close = UIHelper::AssertFindChild<QPushButton*>(UI, "Btn_Close");

	UI->setAttribute(Qt::WA_TransparentForMouseEvents, false); // 鼠标事件穿透
}

void WCloseTitle::ConnectSigSlot()
{
	connect(Btn_Max, &QPushButton::clicked,
	        [this]()
	        {
			if (FollowedWgt->isMaximized()) {
				FollowedWgt->showNormal();
				FollowedWgt->setGeometry(normalGeometry); // 恢复记录的位置和尺寸
			}
			else {
				normalGeometry = FollowedWgt->geometry(); // 保存当前尺寸
				FollowedWgt->showMaximized();
			}
	        }); // 最大化

	connect(Btn_Min, &QPushButton::clicked,
	        [this]()
	        {
		        FollowedWgt->showMinimized();
	        });

	connect(Btn_Close, &QPushButton::clicked, [this]()
	        {
		        QMessageBox msgBox(UI);
		        msgBox.setWindowTitle(tr("提示"));
		        msgBox.setIcon(QMessageBox::Question);
		        msgBox.setText(tr("确定要退出程序吗？"));

		        QPushButton* confirmBtn = msgBox.addButton(tr("确认"), QMessageBox::AcceptRole);
		        QPushButton* cancelBtn = msgBox.addButton(tr("取消"), QMessageBox::RejectRole);

		        msgBox.exec();

		        if (msgBox.clickedButton() == confirmBtn)
		        {
					QApplication::exit(0);
		        }
	        });
}

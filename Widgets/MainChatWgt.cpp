#include "MainChatWgt.h"

#include <QLineEdit>
#include <QPushButton>
#include <QAction>
#include <qcoreevent.h>
#include <qeventloop.h>
#include <QLabel>
#include <qlistwidget.h>
#include <QMouseEvent>
#include <QStackedWidget>
#include <QRandomGenerator>
#include <QSplitter>
#include <QLayout>
#include <QTimer>

#include "ApplyFriendPage.h"
#include "ChatUserWid.h"
#include "Common/GlobalDefine.h"
#include "ChatUserList.h"
#include "WidgetFilesHelper.h"
#include "CloseTitleWgt.h"
#include "LoadingWgt.h"
#include "ChatPageWgt.h"
#include "SearchList.h"
#include "ContactUserList.h"
#include "Common/RedDotNode.h"

WChatWgt::WChatWgt(QWidget* parent):
	ILoadUIWgtBase(WgtFile::MainChatUI, parent)
{

}

WChatWgt::~WChatWgt()
{

}


bool WChatWgt::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == Btn_ResizeSizeFlag)
    {
        switch (event->type())
        {
        case QEvent::Enter:
	        {
		        Btn_ResizeSizeFlag->setCursor(Qt::SizeFDiagCursor); // 右下角缩放光标
		        QEnterEvent* enterEvent = static_cast<QEnterEvent*>(event); // 注意类型转换
                OriginalGeometry = UI->geometry();
		        DragStartPos = enterEvent->globalPos(); // 直接获取全局坐标[3,6](@ref)
		        bInDragBtn = true;
		        return true;
	        }
        case QEvent::Leave:
            Btn_ResizeSizeFlag->unsetCursor(); // 恢复默认光标
            bInDragBtn = false;
            return true;
        }
    }

	if (watched == UI)
	{
		switch (event->type())
		{
		case QEvent::MouseButtonPress:
			{
				QMouseEvent* me = static_cast<QMouseEvent*>(event);
				DragStartPos = me->globalPos();
                qDebug() << "点击按钮时 全局坐标：" << DragStartPos;
				OriginalGeometry = UI->geometry();
                auto rect = GetTitleRect(UI->width(), UIHelper::TITLE_BAR_HEIGHT);
                qDebug() << "返回的标题Rect:" << rect;
                bMouseInTitle= rect.contains(me->globalPos());
				return false;
			}
		case QEvent::MouseMove:
			{
				QMouseEvent* me = static_cast<QMouseEvent*>(event);

				if (me->buttons() & Qt::LeftButton)
				{
					if (bInDragBtn) //缩放界面
					{
						HandleWindowResize(me->globalPos());
					}
					else if(bMouseInTitle) //移动界面
					{
						QPoint delta = me->globalPos() - DragStartPos;
						UI->move(OriginalGeometry.topLeft() + delta);
					}
				}
				return true;
			}
		}
	}

    if (watched == Wgt_AddFriendAear)
    {
	    return AddFriendEvent(watched, event);
    }

	return QObject::eventFilter(watched, event);
}

bool WChatWgt::AddFriendEvent(QObject* watched, QEvent* event)
{
	// 鼠标悬停事件处理 [1,2](@ref)
	if (event->type() == QEvent::Enter)
	{
		watched->setProperty("state", "hover");
		UIHelper::RePolish(Wgt_AddFriendAear);
		return true;
	}
	// 鼠标点击事件处理 [6,7](@ref)
	else if (event->type() == QEvent::MouseButtonPress)
	{
		watched->setProperty("state", "selected");
		emit sigClickedAddFriendArear(); // 触发点击信号
		UIHelper::RePolish(Wgt_AddFriendAear);

		QTimer::singleShot(300, [this,watched]()
		{
			// 500ms后恢复
			if (watched)
			{
				watched->setProperty("state", "normal");
				UIHelper::RePolish(qobject_cast<QWidget*>(watched));
				Stacked_Right->setCurrentWidget(Wgt_ApplyFriendPage->GetUI());
			}
		});

		return true;
	}
	// 鼠标离开事件处理 [1,8](@ref)
	else if (event->type() == QEvent::HoverLeave || event->type() == QEvent::Leave)
	{
		watched->setProperty("state", "normal");
		UIHelper::RePolish(Wgt_AddFriendAear);
		return true;
	}
    return true;
}

void WChatWgt::InitControls()
{
    ChatPage = new WChatPage(UI);
    ChatPage->CreateWgt();

    Stacked_Right= UIHelper::AssertFindChild<QStackedWidget*>(UI, "Stacked_Right");
    Stacked_Right->addWidget(ChatPage->GetUI());
    Stacked_Right->setCurrentWidget(ChatPage->GetUI());

    Edt_Search = UI->findChild<QLineEdit*>("Edt_Search");
    Q_ASSERT(Edt_Search);

    auto Splitter = UIHelper::AssertFindChild<QSplitter*>(UI, "splitter");
    Splitter->setStretchFactor(0, 5);
    Splitter->setStretchFactor(1, 3);

    Btn_MsgModel = UIHelper::AssertFindChild<QPushButton*>(UI, "Btn_MsgModel");
    Btn_UserModel= UIHelper::AssertFindChild<QPushButton*>(UI, "Btn_UserModel");

	Lab_RedDotMsg = UIHelper::AssertFindChild<QLabel*>(UI, "Lab_RedDotMsg");
	Lab_RedDotMsg->setVisible(false);
    SRedDotMgr::Ins().CreateNode("ChatMsg", [this](bool bShow)
    {
	    Lab_RedDotMsg->setVisible(bShow);
    });

    //添加搜索按钮
    SearchAction = new QAction(QIcon(":/Skin/Image/Search.png"), "搜索", Edt_Search);
    Edt_Search->addAction(SearchAction, QLineEdit::LeadingPosition);

    StateWgt_List = UI->findChild<QStackedWidget*>("Stacke_List");
    Q_ASSERT(Edt_Search);

    Wgt_UserLst = UI->findChild<QWidget*>("Wgt_UserLst");
    Q_ASSERT(Wgt_UserLst);

    Wgt_ConLst = UI->findChild<QWidget*>("Wgt_ConLst");
    Q_ASSERT(Wgt_ConLst);

    Wgt_SearchLst = UI->findChild<QWidget*>("Wgt_SearchLst");
    Q_ASSERT(Wgt_SearchLst);

    List_ChatUser = std::make_unique<CChatUserList>();
    List_ChatUser->SetListWgt(UIHelper::AssertFindChild<QListWidget*>(GetUI(), "List_ChatUser"));

    List_Search = std::make_unique<CSearchList>();
    List_Search->SetListWgt(UIHelper::AssertFindChild<QListWidget*>(GetUI(), "Lst_SearchUser"));
    UIHelper::AssertFindChild<QListWidget*>(GetUI(), "Lst_SearchUser")->adjustSize();

	Wgt_ApplyFriendPage = new WApplyFriendPage(UI);
	Wgt_ApplyFriendPage->CreateWgt();
	Stacked_Right->addWidget(Wgt_ApplyFriendPage->GetUI());

    LstContactUser = std::make_unique<CContactUserList>();
    LstContactUser->SetListWgt(UIHelper::AssertFindChild<QListWidget*>(GetUI(), "List_ConUser"));

    Btn_ResizeSizeFlag = UIHelper::AssertFindChild<QPushButton*>(UI, "Btn_ResizeSizeFlag");

    Wgt_WndTitle= UIHelper::AssertFindChild<QWidget*>(UI, "Wgt_WndTitle");

    if(auto LayoutTitle = Wgt_WndTitle->layout())
    {
        Wgt_CloseTitle = new WCloseTitle(UI);
        Wgt_CloseTitle->GetUI()->setParent(UI);
        Wgt_CloseTitle->CreateWgt();
        LayoutTitle->addWidget(Wgt_CloseTitle->GetUI());
    }

    Wgt_AddFriendAear= UIHelper::AssertFindChild<QWidget*>(UI, "Wgt_AddFriendAear");
    Wgt_AddFriendAear->setProperty("state", "normal");

    UI->setWindowFlags(UI->windowFlags() | Qt::FramelessWindowHint|Qt::Window);
    UI->setAttribute(Qt::WA_TranslucentBackground);//透明背景
    UI->installEventFilter(this);  // 关键：将UI的鼠标事件传递到当前对象
    UI->setMouseTracking(true);    // 启用鼠标移动追踪

    Btn_ResizeSizeFlag->installEventFilter(this);
    Wgt_AddFriendAear->installEventFilter(this);

    AddChatUserList();
    StateWgt_List->setCurrentWidget(Wgt_UserLst);
}

void WChatWgt::ConnectSigSlot()
{
	//QLineEdit::clea
	connect(Btn_LineEdtClear, &QPushButton::clicked, [this]()
	{
		ShowSearch(false);
	});


	connect(this, &WChatWgt::sigMainChatWgtSizeChanged, ChatPage, &WChatPage::slotMainChatSizeChanged);

	connect(Btn_MsgModel, &QPushButton::clicked, [this]()
	{
		State = EChatUIMode::ChatMode;
		ShowSearch(false);
	});

	connect(Btn_UserModel, &QPushButton::clicked, [this]()
	{
		State = EChatUIMode::ContactMode;
		ShowSearch(false);
	});

	connect(SearchAction, &QAction::triggered, [this]()
	{
		ShowSearch(true);
	});

	connect(Edt_Search, &QLineEdit::textChanged, [this]()
	{
		ShowSearch(!Edt_Search->text().isEmpty());
	});
}

void WChatWgt::ShowSearch(bool bsearch)
{
    if (bsearch) {
        StateWgt_List->setCurrentWidget(Wgt_SearchLst);
        Mode = EChatUIMode::SearchMode;
    }
    else if (State == EChatUIMode::ChatMode) {
        StateWgt_List->setCurrentWidget(Wgt_UserLst);
        Mode = EChatUIMode::ChatMode;
    }
    else if (State == EChatUIMode::ContactMode) {
        StateWgt_List->setCurrentWidget(Wgt_ConLst);
        Mode = EChatUIMode::ContactMode;
    }
}

void WChatWgt::AddChatUserList()
{
    // 创建QListWidgetItem，并设置自定义的widget
   
}

void WChatWgt::HandleWindowResize(const QPoint& globalPos) {
    QRect newGeo = OriginalGeometry;
    QPoint delta = globalPos - DragStartPos;

    // 调整右下角坐标
    newGeo.setRight(newGeo.right() + delta.x());
    newGeo.setBottom(newGeo.bottom() + delta.y());

    UI->setGeometry(newGeo);
    emit sigMainChatWgtSizeChanged();
}
#include "MainChatWgt.h"

#include <QLineEdit>
#include <QPushButton>
#include <QAction>
#include <qlistwidget.h>
#include <QStackedWidget>
#include "ChatUserList.h"
#include "WidgetFilesHelper.h"
#include <QRandomGenerator>

#include "ChatUserWid.h"
#include "Common/GlobalDefine.h"

std::vector<QString>  strs = { "hello world !",
                             "nice to meet u",
                             "New year，new life",
                            "You have to love yourself",
                            "My love is written in the wind ever since the whole world is you" };

std::vector<QString> heads = {
    ":Skin/Image/HeadIcon01.jpg",
    ":Skin/Image/HeadIcon02.jpg",
    ":Skin/Image/HeadIcon03.jpg",
    ":Skin/Image/HeadIcon04.jpg",
    ":Skin/Image/HeadIcon05.jpg",
	":Skin/Image/HeadIcon06.jpg",
    ":Skin/Image/HeadIcon07.jpg",
    ":Skin/Image/HeadIcon08.jpg"
};

std::vector<QString> names = {
    "llfc",
    "zack",
    "golang",
    "cpp",
    "java",
    "nodejs",
    "python",
    "rust"
};


WChatWgt::WChatWgt(QWidget* parent):
	ILoadUIWgtBase(WgtFile::MainChatUI, parent)
{

}

WChatWgt::~WChatWgt()
{

}

void WChatWgt::InitControls()
{
    Edt_Search = UI->findChild<QLineEdit*>("Edt_Search");
    Q_ASSERT(Edt_Search);

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

    Btn_LineEdtClear= UIHelper::AssertFindChild<QPushButton*>(Edt_Search, "clearButton");

   

}

void WChatWgt::ConnectSigSlot()
{
	//QLineEdit::clea
	connect(Btn_LineEdtClear, &QPushButton::clicked, [this]()
	{
		ShowSearch(false);
	});

    addChatUserList();
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

void WChatWgt::addChatUserList()
{
    // 创建QListWidgetItem，并设置自定义的widget
    for (int i = 0; i < 13; i++) {
        int randomValue = QRandomGenerator::global()->bounded(100); // 生成0到99之间的随机整数
        int str_i = randomValue % strs.size();
        int head_i = randomValue % heads.size();
        int name_i = randomValue % names.size();

        auto* chat_user_wid = new WChatUserWid();
        chat_user_wid->CreateWgt();
        chat_user_wid->SetInfo(names[name_i], heads[head_i], strs[str_i]);
        QListWidgetItem* item = new QListWidgetItem();
        //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
        item->setSizeHint(chat_user_wid->GetUI()->sizeHint());

        List_ChatUser->ListWgt->addItem(item);
        List_ChatUser->ListWgt->setItemWidget(item, chat_user_wid->GetUI());
    }
}

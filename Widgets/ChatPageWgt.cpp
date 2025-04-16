#include "ChatPageWgt.h"

#include <QWidget>
#include <QSplitter>

#include "WidgetFilesHelper.h"
#include "Common/GlobalDefine.h"

WChatPage::WChatPage(QWidget* parent):
	ILoadUIWgtBase(WgtFile::ChatPageWgt,parent)
{
}

void WChatPage::InitControls()
{
	splitter = UIHelper::AssertFindChild<QSplitter*>(UI,"splitter");
	splitter->setStretchFactor(0, 3);
	splitter->setStretchFactor(1, 1);
}

void WChatPage::ConnectSigSlot()
{
	ILoadUIWgtBase::ConnectSigSlot();
}

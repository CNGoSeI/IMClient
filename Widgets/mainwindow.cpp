#include "mainwindow.h"

#include <QPushButton>

#include "WidgetFilesHelper.h"
#include "LoginDlg.h"
#include <QStackedWidget>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , RegWnd(WgtFile::LoadUI(WgtFile::RegDlgPath))
{
    MainStatck = std::make_unique<QStackedWidget>();

    LoginDlg =std::make_unique<DLoginDialog>(WgtFile::LoginDlgPath);
    LoginDlg->CreateWgt();

    MainStatck->addWidget(LoginDlg->GetUI());
    MainStatck->addWidget(RegWnd.get());

    //QMainWindow 拥有 widget 指针的所有权，并会在适当的时候删除它
    setCentralWidget(MainStatck.get());//血泪史 切换centralwgt会导致界面释放
    setFixedSize(300, 500);

    connect(LoginDlg.get(), &DLoginDialog::sigSwitchRegister, this, &MainWindow::slotSwitchReg);
    connect(RegWnd->findChild<QPushButton*>("Btn_Ok"), &QPushButton::clicked, this, [this]()
    {
    	MainStatck->setCurrentWidget(LoginDlg->GetUI());
    });

}

MainWindow::~MainWindow()
{
}

void MainWindow::slotSwitchReg()
{
    MainStatck->setCurrentWidget(RegWnd.get());
}

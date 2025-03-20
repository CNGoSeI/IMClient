#include <QPushButton>
#include <QMouseEvent>
#include <QStackedWidget>
#include <QStyleOption>
#include <QPainter>
#include <QLineEdit>
#include <QApplication>
#include "WidgetFilesHelper.h"
#include "LoginDlg.h"
#include "mainwindow.h"
#include "RegisterWgt.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    MainStatck = std::make_unique<QStackedWidget>();

    LoginDlg =std::make_unique<DLoginDialog>();
    LoginDlg->CreateWgt();
    RegWnd = std::make_unique<WRegisterWgt>();
    RegWnd->CreateWgt();

    MainStatck->addWidget(LoginDlg->GetUI());
    MainStatck->addWidget(RegWnd->GetUI());

    //QMainWindow 拥有 widget 指针的所有权，并会在适当的时候删除它
    setCentralWidget(MainStatck.get());//血泪史 切换centralwgt会导致界面释放

    connect(LoginDlg.get(), &DLoginDialog::sigSwitchRegister, this, [this]()
    {
	    MainStatck->setCurrentWidget(RegWnd->GetUI());
    });
    connect(RegWnd.get(), &WRegisterWgt::sigBtnOkClicked, this, [this]()
    {
	    MainStatck->setCurrentWidget(LoginDlg->GetUI());
    });

    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);//透明背景
    setFixedSize(300, 500);

}

MainWindow::~MainWindow()
{
}

void MainWindow::slotSwitchReg()
{
    ;
}

// 鼠标按下时记录起始位置
void MainWindow::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        bDragging = true;
        DragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    auto clickedWidget = QApplication::widgetAt(event->globalPos());
    if (!qobject_cast<QLineEdit*>(clickedWidget)) {
        focusWidget()->clearFocus();  // 清除当前焦点控件
    }
}

// 鼠标移动时更新窗口位置
void MainWindow::mouseMoveEvent(QMouseEvent* event) {
    if (bDragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPos() - DragPosition);
        event->accept();
    }
}

// 鼠标释放时结束拖动
void MainWindow::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        bDragging = false;
        event->accept();
    }
}

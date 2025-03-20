#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void slotSwitchReg();//切换至注册

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
   std::unique_ptr<class QStackedWidget> MainStatck{ nullptr };
   std::unique_ptr<class DLoginDialog> LoginDlg{nullptr};//登录界面
   std::unique_ptr<class WRegisterWgt>RegWnd{ nullptr };

   bool bDragging{ false };//拖动中？
   QPoint DragPosition;
};
#endif // MAINWINDOW_H

#ifndef CONTROL_SEARCHLIST_H
#define CONTROL_SEARCHLIST_H

#include "CustomList.h"
#include "Common/GlobalDefine.h"

class QListWidgetItem;
using namespace Infos;
class CSearchList: public ICustomList
{
    Q_OBJECT
public:
    CSearchList(QWidget* parent = nullptr);
    void CloseFindDlg();
    void SetSearchEdit(QWidget* edit);
    void AddTipItem();

public slots:
    void slotItemClicked(QListWidgetItem* item);
protected:
    void AfterSetListFunc() override;
    void SelfAddItems() override{};
};

#endif // CONTROL_SEARCHLIST_H

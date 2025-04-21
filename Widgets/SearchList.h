#ifndef CONTROL_SEARCHLIST_H
#define CONTROL_SEARCHLIST_H

#include "CustomList.h"

class QListWidgetItem;

struct FSearchInfo {
    FSearchInfo(int uid, QString name, QString nick, QString desc, int sex);
    int UID;
    QString Name;
    QString Nick;
    QString Desc;
    int Sex;
};

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

};

#endif // CONTROL_SEARCHLIST_H

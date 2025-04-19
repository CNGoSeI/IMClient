#ifndef CONTORL_INPUTTEXTEDIT_H
#define CONTORL_INPUTTEXTEDIT_H
#include <QTextEdit>

class CInputTextEdit: public QTextEdit
{
public:
    explicit  CInputTextEdit(QWidget* parent);
    bool canInsertFromMimeData(const QMimeData* source) const override;//数据属于可插入类型吗

    void insertFromMimeData(const QMimeData* source) override;

private:
    void insertImageFromFile(const QString& path);

    void insertImageFromData(const QImage& img);

    int m_imgCounter = 0;
};
#endif // CONTORL_INPUTTEXTEDIT_H

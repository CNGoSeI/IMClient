#include "InputTextEdit.h"

#include <qimagereader.h>
#include <QMimeData>

CInputTextEdit::CInputTextEdit(QWidget* parent):
	QTextEdit(parent)
{
    // 基础配置
    setAcceptDrops(true);        // 启用拖放功能[9](@ref)
    //setDragEnabled(true);        // 支持拖动操作[9](@ref)


	// 禁用富文本输入
    setAcceptRichText(false); // 阻止用户输入富文本

    // 字体配置
    QFont baseFont("Microsoft YaHei", 11);  // 微软雅黑10px[2](@ref)
    baseFont.setStyleHint(QFont::SansSerif); // 确保字体回退兼容

    // 设置全局字体格式
    QTextCharFormat charFormat;
    charFormat.setFont(baseFont);

    charFormat.clearBackground();  // 清除可能残留的背景格式
    charFormat.clearForeground();  // 清除可能残留的前景格式
    charFormat.setForeground(Qt::black);  // 固定文本颜色

    setCurrentCharFormat(charFormat);
    //setStyleSheet("{background: transparent;}");

    // 动态格式修正
    connect(this, &QTextEdit::textChanged, [=]
    {
	    QTextCursor tmpCursor = textCursor();
	    tmpCursor.mergeCharFormat(charFormat); // 实时覆盖输入格式[7](@ref)
        setCurrentCharFormat(charFormat);
    });
}

bool CInputTextEdit::canInsertFromMimeData(const QMimeData* source) const
{
	return source->hasImage() || source->hasUrls() || QTextEdit::canInsertFromMimeData(source);
}

void CInputTextEdit::insertFromMimeData(const QMimeData* source)
{
    if (source->hasImage()) { // 处理直接拖入的图片数据
        insertImageFromData(qvariant_cast<QImage>(source->imageData()));
    }
    else if (source->hasUrls()) { // 处理从文件系统拖入的图片文件
        foreach(QUrl url, source->urls()) {
            if (QImageReader::supportedImageFormats().contains(url.fileName().section('.', -1).toLower().toLatin1())) {
                insertImageFromFile(url.toLocalFile());
            }
        }
    }
    else {
        QTextEdit::insertFromMimeData(source);
    }
}

void CInputTextEdit::insertImageFromFile(const QString& path)
{
    QImage img(path);
    if (!img.isNull()) {
        QUrl uri(QString("img_%1").arg(++m_imgCounter)); // 生成唯一资源标识
        document()->addResource(QTextDocument::ImageResource, uri, img);

        QTextCursor cursor = textCursor();
        QTextImageFormat format;
        format.setName(uri.toString());
        format.setWidth(img.width() / 2); // 缩放图片宽度为原始50%
        cursor.insertImage(format);
    }
}

void CInputTextEdit::insertImageFromData(const QImage& img)
{
    QUrl uri(QString("img_%1").arg(++m_imgCounter));
    document()->addResource(QTextDocument::ImageResource, uri, img);

    QTextCursor cursor = textCursor();
    cursor.insertImage(uri.toString());
}






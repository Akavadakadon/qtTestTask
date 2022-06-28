#include "MyDelegate.h"
#include <qlineedit>
#include <QLineEdit>
#include <QMenu>
#include <QContextMenuEvent>

MyDelegate::MyDelegate(QObject* parent)
{

}

class MyEditLine :public QLineEdit
{
public:
    MyEditLine(    ) {
    }
    MyEditLine(QWidget* parent = nullptr) :QLineEdit(parent) {}
    void MyEditLine::contextMenuEvent(QContextMenuEvent* event)
    {
        QMenu contextMenu(tr("Context menu"), this);
        contextMenu.addAction(("Context menu too"));
        contextMenu.exec(event->globalPos());
    }
};

void MyDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QItemDelegate::paint(painter, option, index);
}

QWidget* MyDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyleOptionViewItem viewOption(option);
    if (option.state.testFlag(QStyle::State_HasFocus))
        viewOption.state = viewOption.state ^ QStyle::State_None;
    MyEditLine* editor = new MyEditLine(parent);
    return editor;
}

void MyDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    MyEditLine* spinbox = static_cast<MyEditLine*>(editor);
    spinbox->setText(value);
}

void MyDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    MyEditLine* str = static_cast<MyEditLine*>(editor);
    QString value = str->text();
    if (model->data(index).toString() == value)
        return; // Избегать двойного вызова
    model->setData(index, value, Qt::EditRole);
}

void MyDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    editor->setGeometry(option.rect);
}

bool MyDelegate::eventFilter(QObject* object, QEvent* event)
{
    return QItemDelegate::eventFilter(object, event);
}

bool MyDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    return QItemDelegate::editorEvent(event, model, option, index);
}

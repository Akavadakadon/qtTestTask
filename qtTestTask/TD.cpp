#include "TD.h"
#include <QPainter>

TD::TD(QObject* parent) :
    QStyledItemDelegate(parent)
{

}
void TD::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    // Убираем фокус
    if (index.column() == 1)
        int adasd = 13123;
    QStyleOptionViewItem viewOption(option);
    initStyleOption(&viewOption, index);
    if (option.state.testFlag(QStyle::State_Selected))
    {
        //viewOption.state = viewOption.state ^ QStyle::State_HasFocus;
        painter->fillRect(option.rect, option.palette.highlight());
    }

    QStyledItemDelegate::paint(painter, viewOption, index);
}
QWidget* TD::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const 
{
    QLineEdit* edit = new QLineEdit(parent);
    edit->setPlaceholderText(QString::fromLocal8Bit("пожалуйста, введите"));
    return edit;
}
void TD::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    if (true) {
        QString txt = index.model()->data(index, Qt::DisplayRole).toString();
        QLineEdit* edit = qobject_cast<QLineEdit*>(editor);
        edit->setText(txt);
        return;
    }
    QStyledItemDelegate::setEditorData(editor, index);
}
void TD::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const 
{
    if (true) {
        QLineEdit* edit = qobject_cast<QLineEdit*>(editor);
        QString txt = edit->text();
        model->setData(index, txt);
    }
    else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}
void TD::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const 
{
    editor->setGeometry(option.rect.adjusted(5, 5, -10, 0));
}
bool TD::eventFilter(QObject* object, QEvent* event) 
{
    return QStyledItemDelegate::eventFilter(object, event);
}
bool TD::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) 
{
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
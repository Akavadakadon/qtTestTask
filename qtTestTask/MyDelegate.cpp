#include "MyDelegate.h"
#include <qlineedit>
#include <QLineEdit>

MyDelegate::MyDelegate(QObject* parent)
{

}

QWidget* MyDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QLineEdit* editor = new QLineEdit(parent);
    return editor;
}

void MyDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    // Get the value via index of the Model
    QString value = index.model()->data(index, Qt::EditRole).toString();

    // Put the value into the SpinBox
    QLineEdit* spinbox = static_cast<QLineEdit*>(editor);
    spinbox->setText(value);
}

void MyDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    QLineEdit* spinbox = static_cast<QLineEdit*>(editor);
    //spinbox->interpretText();
    QString value = spinbox->text();
    model->setData(index, value, Qt::EditRole);
}

void MyDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    editor->setGeometry(option.rect);
}


#pragma once
#include <QItemDelegate>

class MyDelegate :
    public QItemDelegate
{
    Q_OBJECT
public:
    MyDelegate(QObject* parent = 0);

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option , const QModelIndex& index) const override;

    void setEditorData(QWidget* editor, const QModelIndex& index) const override;

    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option , const QModelIndex& index) const override;

};


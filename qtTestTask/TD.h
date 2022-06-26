#pragma once
#include <qstyleditemdelegate.h>
#include <QLineEdit>


class TD :
    public QStyledItemDelegate
{
    Q_OBJECT
public:
    TD(QObject* parent);
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    bool eventFilter(QObject* object, QEvent* event) override;
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override;

};


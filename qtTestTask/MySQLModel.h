#pragma once
#include <qabstractitemmodel.h>
#include "model.cpp"
class MySQLModel :
    public QAbstractTableModel
{
    Q_OBJECT
private:
    QList<EditorModel> editors;

public:
    MySQLModel(QObject* parent = nullptr);
    MySQLModel(const QList<EditorModel>& editors, QObject* parent = nullptr);

    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void addEditor(EditorModel editor);

    QList<EditorModel> getEditors();



signals:
    void dataChanged(EditorModel changedEditor, int col);
};


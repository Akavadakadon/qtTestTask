#include "MySQLModel.h"
#include "QDebug"

MySQLModel::MySQLModel(QObject* parent) :
    QAbstractTableModel(parent)
{
}
MySQLModel::MySQLModel(const QList<EditorModel>& editors, QObject* parent) :
    QAbstractTableModel(parent), editors(editors)
{
}

int MySQLModel::columnCount(const QModelIndex& parent) const
{
    return 6; 
}

int MySQLModel::rowCount(const QModelIndex& parent) const
{
    return editors.size();
}

void MySQLModel::addEditor(EditorModel editor)
{
    editors.append(editor);
}

QVariant MySQLModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    QStringList list;
    list.append(QString("texteditor"));
    list.append(QString("fileformats"));
    list.append(QString("encoding"));
    list.append(QString("hasintellisense"));
    list.append(QString("hasplugins"));
    list.append(QString("cancompile"));

    if (orientation == Qt::Horizontal)
    {
        return list.at(section);
        switch (role)
        {
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);

        case Qt::DisplayRole:
            return list.at(section);
        default:
            return QVariant();
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

QVariant MySQLModel::data(const QModelIndex & index, int role) const
{
    if (!index.isValid())
        return QVariant();
    int row = index.row();
    int col = index.column();

    if (index.row() >= editors.size() || index.row() < 0)
        return QVariant();

    switch (role)
    {
    case Qt::DisplayRole:
    {
        auto temp = editors[row];
        auto ret = temp.get(col);
        return ret;
    }
    case Qt::EditRole:
    {
        auto temp = editors[row];
        auto ret = temp.get(col);
        return ret;
    }
    }

    return QVariant();
}

bool MySQLModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    int row = index.row();
    int col = index.column();
    if (role == Qt::EditRole) {
        if (!checkIndex(index))
            return false;
        editors[row].set(col, value.toString());
        EditorModel changedEditor = editors[row];
        emit MySQLModel::dataChanged(changedEditor, col);
        return true;
    }
    return QAbstractTableModel::setData(index, value, role);
}

QList<EditorModel> MySQLModel::getEditors()
{
    return editors;
}


//QList<EditorModel> MySQLModel::select()
//{
//
//}


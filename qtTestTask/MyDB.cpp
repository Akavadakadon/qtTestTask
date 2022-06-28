#include "MyDB.h"
#include "model.cpp"
#include <QSqlQuery>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QSqlError>
#include <QDebug>

using namespace std;

int MyDB::Connect()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    //bdInfo::dataBase
    db.setHostName(dbInfo.host);
    QDir databasePath;
    db.setDatabaseName(bdInfo::dataBase);
    bool ok = db.open();
    if (!ok)
        return 0;
    return 0;
}

void MyDB::Close()
{
    db.close();
}

QList<EditorModel> MyDB::Load()
{
    auto tables = db.tables();
    QList<EditorModel> content;

    auto yeye = tables.contains(bdInfo::table);
    if (!yeye || false)
    {
        // Пустая бд, заполняем ее.
        Create(dbInfo.table);
    }
    else
    {
        content= SelectAll();
    }
    return content;
}

//sql CREATE 
void MyDB::Create(QString table)
{
    QSqlQuery query;

    query.prepare("CREATE TABLE IF NOT EXISTS "+ bdInfo::table +"(\
        id	INTEGER NOT NULL primary key AUTOINCREMENT, \
        texteditor	TEXT NOT NULL, \
        fileformats	TEXT, \
        encoding	TEXT, \
        hasintellisense	TEXT, \
        hasplugins	TEXT, \
        cancompile	TEXT);");

    auto res = query.exec();
}

//sql INSERT
void MyDB::Insert(EditorModel newEditor)
{
    QSqlQuery query;
    query.prepare("INSERT INTO " + bdInfo::table + " (texteditor, fileformats, encoding, hasintellisense, hasplugins, cancompile) "
        "VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(newEditor.texteditor);
    query.addBindValue(newEditor.fileformats);
    query.addBindValue(newEditor.encoding);
    query.addBindValue(newEditor.hasintellisense);
    query.addBindValue(newEditor.hasplugins);
    query.addBindValue(newEditor.cancompile);
    auto res1 = query.exec();
    auto s1 = query.lastQuery();
    auto s2 = query.lastError().text();
}

//sql DELETE
bool MyDB::Delete(EditorModel editor)
{
    QSqlQuery query;
    QString req = "DELETE from " + bdInfo::table + " WHERE texteditor = '" + editor.texteditor + "' and \
        fileformats='" + editor.fileformats + "' and \
        encoding='" + editor.encoding + "' and \
        hasintellisense='" + editor.hasintellisense + "' and \
        hasplugins='" + editor.hasplugins + "' and \
        cancompile= '" + editor.cancompile + "'";
    query.prepare(req);
    auto res = query.exec();
    auto s1 = query.lastQuery();
    auto s2 = query.lastError().text();
    return res;
}

//sql UPDATE
void MyDB::Update(EditorModel changedEditor, int col)
{
    QSqlQuery query;
    QString req = "UPDATE  " + bdInfo::table;

    switch (col)
    {
    case 0:
        req += " SET texteditor = '" + changedEditor.texteditor + "' ";
        break;
    case 1:
        req += " SET fileformats = '" + changedEditor.fileformats + "' ";
        break;
    case 2:
        req += " SET encoding = '" + changedEditor.encoding + "' ";
        break;
    case 3:
        req += " SET hasintellisense = '" + changedEditor.hasintellisense + "' ";
        break;
    case 4:
        req += " SET hasplugins = '" + changedEditor.hasplugins + "' ";
        break;
    case 5:
        req += " SET cancompile = '" + changedEditor.cancompile + "' ";
        break;
    default:
        break;
    }

    req += " WHERE ";
    req += (col == 0 ? "true " : "texteditor = '" + changedEditor.texteditor + "' ");
    req += "and ";
    req += (col == 1 ? "true " : "fileformats = '" + changedEditor.fileformats + "' ");
    req += "and ";
    req += (col == 2 ? "true " : "encoding = '" + changedEditor.encoding + "' ");
    req += "and ";
    req += (col == 3 ? "true " : "hasintellisense = '" + changedEditor.hasintellisense + "' ");
    req += "and ";
    req += (col == 4 ? "true " : "hasplugins = '" + changedEditor.hasplugins +"' ");
    req += "and ";
    req += (col == 5 ? "true " : "cancompile = '" + changedEditor.cancompile + "' ");

    query.prepare(req);
    auto res = query.exec();
    auto s1 = query.lastQuery();
    auto s2 = query.lastError().text();
}

//sql SELECT
QList<EditorModel> MyDB::SelectAll()
{
    QSqlQuery query;
    query.prepare("SELECT * from " + bdInfo::table);
    auto res = query.exec();
    auto s1 = query.lastQuery();
    auto s2 = query.lastError().text();
    QList<EditorModel> editorList;

    while (query.next())
    {
        EditorModel editor;
        editor.texteditor = query.value("texteditor").toString();
        editor.fileformats = query.value("fileformats").toString();
        editor.encoding = query.value("encoding").toString();
        editor.hasintellisense = query.value("hasintellisense").toString();
        editor.hasplugins = query.value("hasplugins").toString();
        editor.cancompile = query.value("cancompile").toString();
        editorList.append(editor);
    }
    return editorList;
}

bool MyDB::IfExist(EditorModel editor)
{
    QSqlQuery query;
    QString req = "SELECT * from " + bdInfo::table + " WHERE texteditor = '" + editor.texteditor +"' and \
        fileformats='" + editor.fileformats + "' and \
        encoding='" + editor.encoding + "' and \
        hasintellisense='" + editor.hasintellisense + "' and \
        hasplugins='" + editor.hasplugins + "' and \
        cancompile= '" + editor.cancompile+"'";
    query.prepare(req);
    auto res = query.exec();
    auto s1 = query.lastQuery();
    auto s2 = query.lastError().text();
    int i = 0;
    while (query.next()) { i++; }
    return i;
}

void MyDB::Select()
{

}

QList<EditorModel> MyDB::LoadDefault()
{
    QString path = bdInfo::folder + "/";
    QDir directory(path);
    QStringList files = directory.entryList(QStringList() << "*.xml", QDir::Files);
    QXmlStreamReader xmlReader;
    QList<EditorModel> editorList;

    if (files.size() == 0)
    {
        return editorList;
    }
    int fileOpen;
    for (QString filename : files)
    {
        QFile* file = new QFile(path + filename);
        bool allok = true;
        fileOpen = file->open(QIODevice::ReadOnly | QIODevice::Text);
        xmlReader.setDevice(file);
        EditorModel editor;
        // root texteditor fileformats encoding hasintellisense hasplugins cancompile
        while (!xmlReader.atEnd() && !xmlReader.hasError())
        {
            QXmlStreamReader::TokenType token = xmlReader.readNext();
            if (token != QXmlStreamReader::StartElement)
            {
                continue;
            }
            QString tokenStr1 = xmlReader.name().toString();
            if (tokenStr1 == "texteditor")
                editor.texteditor = xmlReader.readElementText();
            else if (tokenStr1 == "fileformats")
                editor.fileformats = xmlReader.readElementText();
            else if (tokenStr1 == "encoding")
                editor.encoding = xmlReader.readElementText();
            else if (tokenStr1 == "hasintellisense")
                editor.hasintellisense = xmlReader.readElementText();
            else if (tokenStr1 == "hasplugins")
                editor.hasplugins = xmlReader.readElementText();
            else if (tokenStr1 == "cancompile")
                editor.cancompile = xmlReader.readElementText();
            else
                continue;
            if (xmlReader.hasError())
            {
                QString error = xmlReader.errorString();
                error = " xml error: " + error;
                allok = false;
                emit ImportFailed(filename, error);
            }
        }
        editor.id = editorList.size();
        if (allok)
            editorList.append(editor);
        xmlReader.clear();
        file->close();
    }
    return editorList;
}

DBinf MyDB::LoadFile(QString filePath)
{
    QString file, host, dataBase, password, userName, table = "editors";
    QFile f(filePath);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
        return DBinf{ host, dataBase, password, userName, table, userName != "" };;
    QTextStream in(&f);
    file = in.readAll();
    QStringList stringList = file.split('\n');

    for (auto& str : stringList)
    {
        QStringList stringList = str.split(':');
        if (stringList.first() == "host")
            host = stringList.last();
        if (stringList.first() == "dataBase")
            dataBase = stringList.last();
        if (stringList.first() == "password")
            password = stringList.last();
        if (stringList.first() == "userName")
            userName = stringList.last();
    }

    return DBinf{ host, dataBase, password, userName, table, userName!=""};
}

MyDB::MyDB(DBinf _dbInfo):dbInfo(_dbInfo)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

MyDB::MyDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

/*
* 
CREATE TABLE "editors" (
    "id"	INTEGER NOT NULL UNIQUE,
    "texteditor"	TEXT NOT NULL UNIQUE,
    "fileformats"	TEXT,
    "encoding"	TEXT,
    "hasintellisense"	TEXT,
    "hasplugins"	TEXT,
    "cancompile"	TEXT,
    PRIMARY KEY("id" AUTOINCREMENT)
    );


INSERT INTO editors(texteditor, fileformats, encoding, hasintellisense, hasplugins, cancompile)
VALUES(50, 'UserName');

*/

#include "MyDB.h"
#include "model.cpp"
#include <QSqlQuery>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QSqlError>
#include <QDebug>Q_DEBUG

using namespace std;

int MyDB::Connect()
{
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName(dbInfo.host);
        QDir databasePath;
        db.setDatabaseName(dbInfo.dataBase);
        if (dbInfo.login)
        {
            db.setUserName(dbInfo.userName);
            db.setPassword(dbInfo.password);
        }
        bool ok = db.open(); 
        if (!ok)
            return 0;
    return 0;
}

QList<EditorModel> MyDB::Load()
{
    auto tables = db.tables();
    QList<EditorModel> content;

    auto yeye = tables.contains(dbInfo.table);
    // TODO: Удалить true
    if (!yeye || true)
    {
        // Пустая бд, заполняем ее.
        // Загружаем из TestFolder .xml
        content = LoadDefault();
        Create(dbInfo.table);
        for (EditorModel editor: content)
        {
            Insert(editor);
        }
        // TODO: Проверка, есть ли данные с таблице
    }
    else
    {

    }
    Select();
    return content;
}

//sql CREATE 
void MyDB::Create(QString table)
{
    QSqlQuery query;

    query.prepare("CREATE TABLE IF NOT EXISTS "+ table +"(\
        id	INTEGER NOT NULL primary key AUTOINCREMENT, \
        texteditor	TEXT NOT NULL UNIQUE, \
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
    query.prepare("INSERT INTO " + dbInfo.table + " (texteditor, fileformats, encoding, hasintellisense, hasplugins, cancompile) "
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
void MyDB::Delete()
{
        
}

//sql UPDATE
void MyDB::Update()
{

}

//sql SELECT
void MyDB::Select()
{
    QSqlQuery query;
    query.prepare("SELECT * from " + dbInfo.table);
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

}

QList<EditorModel> MyDB::LoadDefault()
{
    QString path = "TestFolder/";
    QDir directory(path);
    QStringList files = directory.entryList(QStringList() << "*.xml", QDir::Files);
    QXmlStreamReader xmlReader;
    QList<EditorModel> editorList;
    if (files.size() == 0)
    {
        path = "../TestFolder/";
        directory = QDir(path);
        files = directory.entryList(QStringList() << "*.xml", QDir::Files);
    }
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
                //QString error = xmlReader.errorString();
                //error = " xml error: " + editor.texteditor + " " + error;
                allok = false;
            }
        }
        if (allok)
            editorList.append(editor);
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

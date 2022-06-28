#include "myThread.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QMessageBox>
#include "ImportWindow.h"


MyDB* myThread::myDB = new MyDB();

myThread::myThread()
{
}

void myThread::rmEditor(EditorModel selectedRow) //
{
    if (myDB->IfExist(selectedRow))
        if (myDB->Delete(selectedRow))
        {
            myModel = new MySQLModel(myDB->SelectAll());

            emit myThread::DataLoaded(myModel);
            return;
        }
}

void myThread::LoadDB()
{
    myDB->Close();
    auto dbInfo = MyDB::LoadFile("bd.txt");

    qDebug() << bdInfo::dataBase;

    myDB = new MyDB();

    myDB->Connect();
    auto content = myDB->Load();
    myModel= new MySQLModel(content);

    connect(myModel, &MySQLModel::dataChanged, myDB, &MyDB::Update);

    emit myThread::DataLoaded(myModel);
}

void myThread::ImportXml()
{
    //QThread:msleep(10000);
    QList<EditorModel> modelEditors = myModel->getEditors();


    auto content = myDB->LoadDefault();
    int counter = 0;
    for (int i = 0; i < content.count(); i++)
    {
        if (!myDB->IfExist(content[i]))
        {
            modelEditors.append(content[i]);
            myDB->Insert(content[i]);
            emit ImportSuccessed(content[i].texteditor);
            counter++;
        }
        else
        {
            emit ImportFailed(content[i].texteditor, QString::fromLocal8Bit("Дубликат"));
        }
    }
    //QList<EditorModel> content;
    myModel = new MySQLModel(modelEditors);

    //emit myThread::PopMsgBox(QString("Exported %1 editors"), "XML");
    emit myThread::DataLoaded(myModel);
}

void myThread::ExportToXML(const EditorModel selectedRow)
{
    //QThread:msleep(10000);
    int i = 0;
    QString path = bdInfo::folder + "/" + selectedRow.texteditor + ".xml";
    while (QFile::exists(path))
        path = bdInfo::folder + "/" + selectedRow.texteditor + "(" + QString::number(++i) + ")" + ".xml";

    QFile file(path);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("root");
    stream.writeTextElement("texteditor",selectedRow.texteditor);
    stream.writeTextElement("fileformats", selectedRow.fileformats);
    stream.writeTextElement("encoding", selectedRow.encoding);
    stream.writeTextElement("hasintellisense", selectedRow.hasintellisense);
    stream.writeTextElement("hasplugins", selectedRow.hasplugins);
    stream.writeTextElement("cancompile", selectedRow.cancompile);
    stream.writeEndElement();
    stream.writeEndDocument();
    file.close();
}

void myThread::UpdateEditor(EditorModel selectedRow, EditorModel updatedEditor)
{
    //QThread:msleep(10000);
    if (!myDB->IfExist(updatedEditor))
    {
        if (myDB->IfExist(selectedRow))
            myDB->Delete(selectedRow);
        myDB->Insert(updatedEditor);
    }
    auto content = myDB->SelectAll();
    myModel = new MySQLModel(content);
    emit myThread::DataLoaded(myModel);
}


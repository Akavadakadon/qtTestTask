#pragma once
#include <qthread.h>
#include "model.cpp"
#include "MyDB.h"
#include "MySQLModel.h"
#include <qDebug>

class myThread :
    public QThread
{
    Q_OBJECT
private:
    static MyDB* myDB;
    MySQLModel* myModel;
public:
    myThread();
public slots:
    void LoadDB();
    void rmEditor(EditorModel selectedRow);
    void ImportXml();
    void ExportToXML(const EditorModel selectedRow);
    void UpdateEditor(EditorModel selectedRow, EditorModel updatedEditor);
signals:
    void DataLoaded(MySQLModel* myModel);
    void PopMsgBox(QString text, QString title);
    void ImportSuccessed(QString fileName);
    void ImportFailed(QString fileName, QString error);
};


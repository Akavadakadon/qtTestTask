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
    void Start();
    void rmEditor(int row);
    void rmEditor(EditorModel selectedRow);
    void exportXml();
    void dataChanged()
    {

    }
    //void DataReady(MySQLModel* myModel);
signals:
    void dataLoaded(MySQLModel* myModel);
    void PopMsgBox(QString text, QString title);
    //TODO: Replace dataLoaded with dataReady
};


#pragma once
#include <qthread.h>
#include "model.cpp"
#include "MyDB.h"
#include "MySQLModel.h"

class myThread :
    public QThread
{
    Q_OBJECT
private:
    MyDB* myDB;
    MySQLModel* myModel;
public:
    myThread();
public slots:
    void Start();
    void rmEditor(int row);
    void dataChanged()
    {

    }
    //void DataReady(MySQLModel* myModel);
signals:
    void dataLoaded(MySQLModel* myModel);
    //TODO: Replace dataLoaded with dataReady
};


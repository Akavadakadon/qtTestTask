#include "myThread.h"

myThread::myThread()
{
}

void myThread::rmEditor(int row)
{
    //TODO: �������� �� ���������� � �� ��


    //TODO: �������� ���� �������, ���������� �� �������
    //dataLoaded(MySQLModel * myModel)
}
//
//void myThread::DataReady(MySQLModel* myModel)
//{
//    emit myThread::DataLoaded(myModel);
//}

void myThread::Start()
{
    auto dbInfo = MyDB::LoadFile("bd.txt");
    myDB = new MyDB(dbInfo);

    myDB->Connect();
    auto content = myDB->Load();
    //TODO: ������ ���� �� ������ ��� ��������
    myModel= new MySQLModel(content);


    connect(myModel, &MySQLModel::dataChanged, myDB, &MyDB::Update);
    connect(myModel, &MySQLModel::dataChanged, myDB, &MyDB::Update);
    //connect(myDB, &MyDB::DataReady, [this](MySQLModel* myModel) {DataLoaded(myModel); });

    emit myThread::dataLoaded(myModel);

}
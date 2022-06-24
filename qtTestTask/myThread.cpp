#include "myThread.h"

myThread::myThread()
{

}

void myThread::Start()
{
    auto dbInfo = MyDB::LoadFile("bd.txt");
    myDB = new MyDB(dbInfo);

    myDB->Connect();
    auto content = myDB->Load();
    //TODO: ������ ���� �� ������ ��� ��������
    myModel= new MySQLModel(content);

    emit myThread::dataLoaded(myModel);
}
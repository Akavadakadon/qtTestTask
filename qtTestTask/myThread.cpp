#include "myThread.h"

myThread::myThread()
{

}

void myThread::Start()
{
    auto dbInfo = MyDB::LoadFile("bd.txt");
    myDB = new MyDB(dbInfo);

    myDB->Connect();
    auto ass = myDB->Load();
    myModel= new MySQLModel(ass);

    emit myThread::dataLoaded(myModel);
}
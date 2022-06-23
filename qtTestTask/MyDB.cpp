#include "MyDB.h"
#include <fstream>//sstream
#include <sstream>//sstream
#include <list>

using namespace std;

int MyDB::Connect()
{
    try {
        //db.setHostName(QString::fromStdString(dbInfo.host));
        db.setDatabaseName(QString::fromStdString(dbInfo.dataBase));
        if (dbInfo.login)
        {
            db.setUserName(QString::fromStdString(dbInfo.userName));
            db.setPassword(QString::fromStdString(dbInfo.password));
        }
        bool ok = db.open(); //??
    }
    catch (exception e)
    {
        emit error(e.what());
        return -1;
    }
    return 0;
}

DBinf MyDB::LoadFile(std::string filePath)
{
    fstream fileStream(filePath);
    if (fileStream.fail())
    {
        throw string("No such file");
    }
    stringstream strStream;
    string file, host, dataBase, password, userName;
    const char *anotherList[] = {"host", "dataBase", "password", "userName",""};
    list<string> stringList;
    strStream << fileStream.rdbuf();
    file = string(strStream.str())+'\n';
    fileStream.close();

    int pos = 0;
    while ((pos = file.find('\n')) != -1)
    {
        string line = file.substr(0, pos);
        stringList.push_back(line);
        file.erase(0, pos + 1);
    }

    for (auto& str : stringList)
    {
        if((pos = str.find(':'))==-1)
            continue;
        string key = str.substr(0, pos);
        string value = str.substr(pos + 1, str.length() - pos);
        if (key == "host")
            host = value;
        if (key == "dataBase")
            dataBase = value;
        if (key == "password")
            password = value;
        if (key == "userName")
            userName = value;
    }

    return DBinf{ host, dataBase, password, userName, userName!=""};
}

MyDB::MyDB(DBinf _dbInfo):dbInfo(_dbInfo)
{
    db = QSqlDatabase::addDatabase("QSQLITE2 ");
}
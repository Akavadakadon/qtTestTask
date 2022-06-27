#include "myThread.h"

MyDB* myThread::myDB = new MyDB();

myThread::myThread()
{
}

void myThread::rmEditor(int row) //EditorModel selectedRow
{
    //TODO: �������� �� ���������� � �� ��


    //TODO: �������� ���� �������, ���������� �� �������
    //dataLoaded(MySQLModel * myModel)


}
void myThread::rmEditor(EditorModel selectedRow) //
{
    //TODO: �������� �� ���������� � �� ��

    if (myDB->IfExist(selectedRow))
        if (myDB->Delete(selectedRow))
        {
            myModel = new MySQLModel(myDB->SelectAll());

            emit myThread::dataLoaded(myModel);
            return;
        }
    
    //TODO: ����, ��� ������ �������
    //dataLoaded(MySQLModel * myModel)

}

void myThread::Start()
{
    auto dbInfo = MyDB::LoadFile("bd.txt");

    qDebug() << bdInfo::dataBase;

    myDB = new MyDB();

    myDB->Connect();
    auto content = myDB->Load();
    //TODO: ������ ���� �� ������ ��� ��������
    myModel= new MySQLModel(content);

    connect(myModel, &MySQLModel::dataChanged, myDB, &MyDB::Update);
    //connect(myDB, &MyDB::DataReady, [this](MySQLModel* myModel) {DataLoaded(myModel); });

    emit myThread::dataLoaded(myModel);
    emit myThread::PopMsgBox(QString("Loaded %1 editors").arg(myModel->rowCount()), "DB");
    //exportXml();
}

void myThread::exportXml()
{
    QList<EditorModel> modelEditors = myModel->getEditors();

    auto content = myDB->LoadDefault();
    int counter = 0;
    for (int i = 0; i < content.count(); i++)
    {
        if (!myDB->IfExist(content[i]))
        {
            modelEditors.append(content[i]);
            //TODO: �������� insert
            counter++;
        }
    }
    //QList<EditorModel> content;
    myModel = new MySQLModel(modelEditors);

    emit myThread::dataLoaded(myModel);
    emit myThread::PopMsgBox(QString("Exported %1 editors").arg(counter), "XML");
}

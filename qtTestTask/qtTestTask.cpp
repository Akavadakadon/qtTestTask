#include "qtTestTask.h"
#include "myThread.h"

//#include "MyDB.h"

qtTestTask::qtTestTask(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.pushButton, &QPushButton::clicked, this, &qtTestTask::ClearTable);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &qtTestTask::LoadTable);

    //auto asd = MyDB::LoadFile("bd.txt");
}

void qtTestTask::ClearTable() 
{

}

void qtTestTask::LoadTable() 
{
    //auto dbInfo = MyDB::LoadFile("bd.txt");
    myThread* thread = new myThread();

    //MyDB* myDB = new MyDB(dbInfo);
    //myDB->moveToThread(thread);

    //connect(myDB, &MyDB::error, [this]() {QMessageBox::warning(this, "Ошибка", ""); });
    // инсерт
    // апдейт
    // делит

    //MySQLModel* myModel= new MySQLModel();
    //ui.tableView->setModel(myModel);
    //myModel->moveToThread(thread);
    connect(thread, &myThread::started, thread, &myThread::Start);
    connect(thread, &myThread::dataLoaded, this, [this](MySQLModel* myModel) {Display(myModel); });
    thread->start();


    //connect(myDB, &MyDB::initiated, this, [this, myModel](QList<EditorModel> db) {myModel = new MySQLModel(); ui.tableView->setModel(myModel); });
    //ui.tableView->setModel(myModel);
}

void qtTestTask::Display(MySQLModel* myModel)
{
    ui.tableView->setModel(myModel); // 
}

qtTestTask::~qtTestTask()
{}

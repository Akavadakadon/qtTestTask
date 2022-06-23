#include "qtTestTask.h"
#include "MyDB.h"
#include <list>
#include <QMessageBox>

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
    auto dbInfo = MyDB::LoadFile("bd.txt");
    QThread* thread = new QThread();
    MyDB* myDB = new MyDB(dbInfo);
    myDB->moveToThread(thread);

    connect(thread, &QThread::started, myDB, &MyDB::Connect);
    connect(myDB, &MyDB::error, [this](const char* error) {QMessageBox::warning(this, "Ошибка", error); });
    // инсерт
    // апдейт
    // делит

    thread->start();
}

qtTestTask::~qtTestTask()
{}

#include "qtTestTask.h"
#include "myThread.h"
#include <QMouseEvent>
#include <QStandardItemModel>
#include <QModelIndex>


//#include "MyDB.h"

void qtTestTask::viewClicked(const QModelIndex& idx)
{
    ui.tableView->openPersistentEditor(ui.tableView->model()->index(idx.row(), idx.column()));
    qDebug() << QObject::trUtf8("Item %1 has been clicked.").arg(idx.data().toString());
}

qtTestTask::qtTestTask(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.pushButton, &QPushButton::clicked, this, &qtTestTask::ClearTable);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &qtTestTask::LoadTable);
    connect(ui.tableView, &QTableView::clicked, this, &qtTestTask::viewClicked);

    //connect(ui.tableView, &QTableView::clicked, SLOT(viewClicked(const QModelIndex & idx)));


    myDelegate = new MyDelegate(this);
    TD* myDelegate1 = new TD(this);
    ui.tableView->setItemDelegate(myDelegate);
}

void qtTestTask::mouseReleaseEvent(QMouseEvent* event)
{
    //QMouseEvent* evt = new QMouseEvent(QEvent::MouseButtonRelease,
    //    QPointF(1, 1), // Cannot use lineEdit->width()/2 somehow.
    //    Qt::LeftButton,
    //    Qt::LeftButton,
    //    Qt::NoModifier);
    //QApplication::postEvent(ui.tableView, evt);

}

void qtTestTask::ClearTable() 
{
    // Create a new model
    // QStandardItemModel(int rows, int columns, QObject * parent = 0)
    QStandardItemModel* model = new QStandardItemModel(4, 2, this);

    // Generate data
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 2; col++)
        {
            QModelIndex index
                = model->index(row, col, QModelIndex());
            // 0 for all data
            model->setData(index, 0);
        }
    }
    // Attach (tie) the model to the view
    ui.tableView->setModel(model);

    // Tie the View with the new MyDelegate instance
    // If we don not set this, it will use default delegate
}

void qtTestTask::LoadTable() 
{
    myThread* thread = new myThread();

    connect(thread, &myThread::started, thread, &myThread::Start);
    connect(thread, &myThread::dataLoaded, this, [this](MySQLModel* myModel) {Display(myModel); });

    thread->start();
}

void qtTestTask::Mouse1(const QModelIndex& index)
{

}
void qtTestTask::Mouse(QMouseEvent* event)
{

}

void qtTestTask::Display(MySQLModel* myModel)
{
    ui.tableView->setModel(myModel); // 
    for (size_t i = 0; i < myModel->columnCount(); i++) //a structure from a function that adds rows dynamically
    {
        for (size_t j = 0; j < myModel->rowCount(); j++) //a structure from a function that adds rows dynamically
        {
            //ui.tableView->openPersistentEditor(ui.tableView->model()->index(j, i));
        }
    }
}


qtTestTask::~qtTestTask()
{}

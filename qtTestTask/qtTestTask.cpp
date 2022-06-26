#include "qtTestTask.h"
#include <QMouseEvent>
#include <QStandardItemModel>
#include <QModelIndex>

void qtTestTask::viewClicked(const QModelIndex& idx)
{
    ui.tableView->openPersistentEditor(ui.tableView->model()->index(idx.row(), idx.column()));
    qDebug() << QObject::trUtf8("Item %1 has been clicked.").arg(idx.data().toString());
}

qtTestTask::qtTestTask(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.pushButton, &QPushButton::clicked, this, &qtTestTask::ClearTable);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &qtTestTask::LoadTable);
    connect(ui.tableView, &QTableView::clicked, this, &qtTestTask::viewClicked);


    ui.tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui.tableView, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(tableContextMenu(const QPoint&)));

    myDelegate = new MyDelegate(this);
    TD* myDelegate1 = new TD(this);
    ui.tableView->setItemDelegate(myDelegate);
}


void qtTestTask::tableContextMenu(const QPoint& pos)
{
    QModelIndex click = ui.tableView->indexAt(pos);
    int row = click.row();
    if (row == -1)
        return;
    qDebug() << QString("Row %1 has been clicked").arg(row);

    QMenu contextMenu(tr("Context menu"), this);
    QAction action1(QString::fromLocal8Bit("Удалить редактор"), this);

    connect(&action1, &QAction::triggered, [this, row]() { thread->rmEditor(row); });
    contextMenu.addAction(&action1);
    contextMenu.exec(mapToGlobal(pos));

}
void qtTestTask::rmEditor(int row)
{

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
    QStandardItemModel* model = new QStandardItemModel(4, 2, this);

    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 2; col++)
        {
            QModelIndex index
                = model->index(row, col, QModelIndex());
            model->setData(index, 0);
        }
    }
    ui.tableView->setModel(model);
}

void qtTestTask::LoadTable() 
{
    thread = new myThread();

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
}


qtTestTask::~qtTestTask()
{}

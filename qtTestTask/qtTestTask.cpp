#include "qtTestTask.h"
#include <QMouseEvent>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QMessageBox>


QString bdInfo::dataBase = "testTask.db";
QString bdInfo::folder = "TestFolder";
QString bdInfo::host = "localhost";
QString bdInfo::table = "editors";

qtTestTask::qtTestTask(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.pushButton, &QPushButton::clicked, this, &qtTestTask::ClearTable_clicked);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &qtTestTask::LoadTable_clicked);
    connect(ui.pushButton_3, &QPushButton::clicked, this, &qtTestTask::Settings_clicked);
    connect(ui.pushButton_4, &QPushButton::clicked, this, &qtTestTask::Export_clicked);
    connect(ui.tableView, &QTableView::clicked, this, &qtTestTask::viewClicked);
    ui.tableView->verticalHeader()->setVisible(false);

    ui.tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui.tableView, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(tableContextMenu(const QPoint&)));



    myDelegate = new MyDelegate(this);
    TD* myDelegate1 = new TD(this);
    ui.tableView->setItemDelegate(myDelegate);
}

void qtTestTask::viewClicked(const QModelIndex& idx)
{
    ui.tableView->openPersistentEditor(ui.tableView->model()->index(idx.row(), idx.column()));
    qDebug() << QObject::trUtf8("Item %1 has been clicked.").arg(idx.data().toString());
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

    //
    //ui.tableView->model()->index(idx.row(), idx.column());
    auto colNum = ui.tableView->model()->columnCount();
    //

    connect(&action1, &QAction::triggered, [this, row, colNum]() {
        EditorModel selectedRow;
        for (int i = 0; i < colNum; i++)
            selectedRow.set(i, ui.tableView->model()->data(ui.tableView->model()->index(row, i)).toString());
        thread->rmEditor(selectedRow);
        });
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

void qtTestTask::ClearTable_clicked()
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

void qtTestTask::LoadTable_clicked()
{
    thread = new myThread();

    connect(thread, &myThread::started, thread, &myThread::Start);
    connect(thread, &myThread::dataLoaded, this, [this](MySQLModel* myModel) {Display(myModel); });

    connect(thread, &myThread::PopMsgBox, this, &qtTestTask::msgBox);
    connect(ui.pushButton_4, &QPushButton::clicked, thread, &myThread::exportXml);

    thread->start();
}

void qtTestTask::Settings_clicked()
{
    SettingsDialog sinfWind;

    sinfWind.exec();
}

void qtTestTask::Export_clicked()
{
    //thread->exportXml();
}

void qtTestTask::Mouse1(const QModelIndex& index)
{

}

void qtTestTask::Mouse(QMouseEvent* event)
{

}

void qtTestTask::Display(MySQLModel* myModel)
{
    ui.tableView->reset();
    ui.tableView->repaint();
    ui.tableView->setModel(myModel); // refreshTable
}

void qtTestTask::msgBox(QString text, QString title)
{
    QMessageBox* msgBox = new QMessageBox();
    msgBox->setWindowTitle(title);
    msgBox->setText(text);
    msgBox->exec();
}

qtTestTask::~qtTestTask()
{}

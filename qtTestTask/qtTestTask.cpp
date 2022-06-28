#include "qtTestTask.h"
#include <QMouseEvent>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QMessageBox>
#include "EditorWindow.h"


QString bdInfo::dataBase = "testTask.db";
QString bdInfo::folder = "TestFolder";
QString bdInfo::host = "localhost";
QString bdInfo::table = "editors";
QModelIndex prevClick;


qtTestTask::qtTestTask(QWidget* parent)
    : QMainWindow(parent)
{

    ui.setupUi(this);
    thread = new myThread();
    qRegisterMetaType<EditorModel>();

    // ќткул€чить resize
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    this->statusBar()->setSizeGripEnabled(false);

    connect(ui.pushButton, &QPushButton::clicked, this, &qtTestTask::ClearTable_clicked);
    connect(ui.tableView, &QTableView::doubleClicked, this, &qtTestTask::viewDoubleClicked);
    connect(ui.tableView, &QTableView::clicked, this, &qtTestTask::viewClicked);
    ui.tableView->verticalHeader()->setVisible(false);
    //connect(ui.pushButton_3, &QPushButton::clicked, this, &qtTestTask::Settings_clicked);
    //connect(ui.pushButton_2, &QPushButton::clicked, this, &qtTestTask::LoadTable_clicked);
    ui.pushButton_3->setEnabled(false);
    ui.pushButton_3->setVisible(false);
    ui.pushButton_2->setEnabled(false);
    ui.pushButton_2->setVisible(false);

    ui.tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui.tableView, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(tableContextMenu(const QPoint&)));
    connect(ui.pushButton_4, &QPushButton::clicked, thread, &myThread::ImportXml);

    myDelegate = new MyDelegate(this);
    ui.tableView->setItemDelegate(myDelegate);

    connect(thread, &myThread::started, thread, &myThread::LoadDB);
    connect(thread, &myThread::DataLoaded, this, [this](MySQLModel* myModel) {Display(myModel); });
    connect(thread, &myThread::PopMsgBox, this, &qtTestTask::msgBox);

    QThread* tread1 = new QThread();
    thread->moveToThread(tread1);
    connect(tread1, &QThread::started, thread, &myThread::LoadDB);
    connect(this, &qtTestTask::UpdateEditor, thread, &myThread::UpdateEditor);
    tread1->start();
}

//TODO: ѕереработать SQLmodel убирать режим редактировани€ при смене покуса

void qtTestTask::viewDoubleClicked(const QModelIndex& idx)
{
    auto click = ui.tableView->model()->index(idx.row(), idx.column());
    ui.tableView->openPersistentEditor(click);
    prevClick = click;
    qDebug() << QObject::trUtf8("Item %1 has been clicked.").arg(idx.data().toString());
}

void qtTestTask::viewClicked(const QModelIndex& idx)
{
    ui.tableView->closePersistentEditor(prevClick);
}

void qtTestTask::tableContextMenu(const QPoint& pos)
{
    QModelIndex click = ui.tableView->indexAt(pos);
    int row = click.row();
    if (row == -1)
        return;
    qDebug() << QString("Row %1 has been clicked").arg(row);

    QMenu contextMenu(tr("Context menu"), this);
    QAction action1(QString::fromLocal8Bit("”далить редактор"), this);
    QAction action2(QString::fromLocal8Bit("Ёкспортировать редактор"), this);
    QAction action3(QString::fromLocal8Bit("»зменить редактор"), this);

    auto colNum = ui.tableView->model()->columnCount();

    EditorModel selectedRow;
    for (int i = 0; i < colNum; i++)
        selectedRow.set(i, ui.tableView->model()->data(ui.tableView->model()->index(row, i)).toString());

    connect(&action1, &QAction::triggered, [this, selectedRow]() {
        thread->rmEditor(selectedRow);
        });

    connect(&action2, &QAction::triggered, [this, selectedRow]() {
        thread->ExportToXML(selectedRow);
        });

    connect(&action3, &QAction::triggered, [this, selectedRow]() {
        EditorWindow* wind = new EditorWindow(selectedRow);
        wind->exec();
        //QMetaObject::invokeMethod(thread, "UpdateEditor");
        //thread->UpdateEditor(selectedRow, wind->updatedEditor);

        emit UpdateEditor(selectedRow, wind->updatedEditor);

        });
    //connect(&action3, &QAction::triggered, [this, row, colNum]() {
    //    EditorModel selectedRow;
    //    for (int i = 0; i < colNum; i++)
    //        selectedRow.set(i, ui.tableView->model()->data(ui.tableView->model()->index(row, i)).toString());
    //    thread->ExportToXML(selectedRow);
    //    });
    contextMenu.addAction(&action1);
    contextMenu.addAction(&action2);
    contextMenu.addAction(&action3);
    contextMenu.exec(mapToGlobal(pos));

}

void qtTestTask::ClearTable_clicked()
{
    MySQLModel* model = new MySQLModel();
    ui.tableView->setModel(model);
}

void qtTestTask::LoadTable_clicked()
{
    //thread = new myThread();

    //connect(thread, &myThread::started, thread, &myThread::LoadDB);
    //connect(thread, &myThread::DataLoaded, this, [this](MySQLModel* myModel) {Display(myModel); });

    //connect(thread, &myThread::PopMsgBox, this, &qtTestTask::msgBox);

    //thread->start();
}

void qtTestTask::Settings_clicked()
{
    SettingsDialog sinfWind;

    sinfWind.exec();
}

void qtTestTask::Display(MySQLModel* myModel)
{
    ui.tableView->setModel(myModel);
    int width = ui.tableView->width() / myModel->columnCount();
    for(int i =0;i< myModel->columnCount(); i++)
        ui.tableView->setColumnWidth(i,width);
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

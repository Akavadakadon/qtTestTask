#pragma once

#include <QtWidgets/QMainWindow>
#include <qDebug>
#include "ui_qtTestTask.h"
#include "MySQLModel.h"
#include "MyDelegate.h"
#include "myThread.h"
#include "model.cpp"
#include "SettingsDialog.h"
#include <QMenu>

class qtTestTask : public QMainWindow
{
    Q_OBJECT

public:
    qtTestTask(QWidget *parent = nullptr);
    ~qtTestTask();
    MyDelegate* myDelegate;

private:
    Ui::qtTestTaskClass ui;
    myThread* thread;

private slots:
    void ClearTable_clicked();
    void LoadTable_clicked();
    void Settings_clicked();
    
    void Display(MySQLModel* myModel);
    void msgBox(QString text, QString title = "");
    void viewDoubleClicked(const QModelIndex& idx);
    void viewClicked(const QModelIndex& idx);
    void tableContextMenu(const QPoint&);

signals:
    void UpdateEditor(EditorModel selectedRow, EditorModel updatedEditor);
};

Q_DECLARE_METATYPE(EditorModel)

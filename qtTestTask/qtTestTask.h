#pragma once

#include <QtWidgets/QMainWindow>
#include <qDebug>
#include "ui_qtTestTask.h"
#include "MySQLModel.h"
#include "TD.h"
#include "MyDelegate.h"
#include "myThread.h"
#include "model.cpp"
#include "SettingsDialog.h"

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
    void rmEditor(int row);
    void ClearTable_clicked();
    void LoadTable_clicked();
    void Settings_clicked();
    void Export_clicked();
    
    void Display(MySQLModel* myModel);
    void msgBox(QString text, QString title = "");
    void Mouse(QMouseEvent* event);
    void Mouse1(const QModelIndex& index);
    void viewClicked(const QModelIndex& idx);
    void mouseReleaseEvent(QMouseEvent* event) override;
    void tableContextMenu(const QPoint&);
};

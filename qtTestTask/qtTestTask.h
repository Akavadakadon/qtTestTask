#pragma once

#include <QtWidgets/QMainWindow>
#include <qDebug>
#include "ui_qtTestTask.h"
#include "MySQLModel.h"
#include "TD.h"
#include "MyDelegate.h"

class qtTestTask : public QMainWindow
{
    Q_OBJECT

public:
    qtTestTask(QWidget *parent = nullptr);
    ~qtTestTask();
    MyDelegate* myDelegate;

private:
    Ui::qtTestTaskClass ui;

private slots:
    void ClearTable();
    void LoadTable();
    void Display(MySQLModel* myModel);
    void Mouse(QMouseEvent* event);
    void Mouse1(const QModelIndex& index);
    void viewClicked(const QModelIndex& idx);
    void mouseReleaseEvent(QMouseEvent* event) override;
};

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qtTestTask.h"

class qtTestTask : public QMainWindow
{
    Q_OBJECT

public:
    qtTestTask(QWidget *parent = nullptr);
    ~qtTestTask();

private:
    Ui::qtTestTaskClass ui;
};

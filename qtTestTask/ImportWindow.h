#pragma once

#include <QDialog>
#include "ui_ImportWindow.h"

class ImportWindow : public QDialog
{

public:
	ImportWindow(QWidget *parent = nullptr);
	~ImportWindow();
public slots:
    void ImportSuccessed(QString fileName);
    void ImportFailed(QString fileName, QString error);

private:
	Ui::ImportWindowClass ui;
    int SuccessCounter;
    int FailCounter;
};

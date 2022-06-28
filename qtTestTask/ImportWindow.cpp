#include "ImportWindow.h"

ImportWindow::ImportWindow(QWidget *parent)
	: QDialog(parent)
{
	SuccessCounter = 0;
	FailCounter = 0;
	ui.setupUi(this);
	ui.lineEdit->setText(QString::fromLocal8Bit("Успешно: ") + QString::number(SuccessCounter));
	ui.lineEdit_2->setText(QString::fromLocal8Bit("Ошибка: ") + QString::number(FailCounter));
	ui.lineEdit->setReadOnly(true);
	ui.lineEdit_2->setReadOnly(true);

	ui.textEdit_2->setReadOnly(true);
}

ImportWindow::~ImportWindow()
{
	SuccessCounter = 0;
	FailCounter = 0;
}

void ImportWindow::ImportSuccessed(QString fileName)
{
    SuccessCounter++;
	ui.lineEdit->setText(QString::fromLocal8Bit("Успешно: ")+ QString::number(SuccessCounter));
}
void ImportWindow::ImportFailed(QString fileName, QString error)
{
    FailCounter++;
	ui.lineEdit_2->setText(QString::fromLocal8Bit("Ошибка: ") + QString::number(FailCounter));
	ui.textEdit_2->append(QString::number(FailCounter) + " " + fileName + ": " + error + "\n");
}

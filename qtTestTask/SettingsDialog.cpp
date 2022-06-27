#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.lineEdit->setText(bdInfo::dataBase);
	ui.lineEdit_2->setText(bdInfo::table);
	ui.lineEdit_3->setText(bdInfo::folder);

	connect(ui.pushButton, &QPushButton::clicked, this, &SettingsDialog::Accept_click);
	connect(ui.pushButton_2, &QPushButton::clicked, this, &SettingsDialog::Cancel_click);
}

SettingsDialog::~SettingsDialog()
{}


void SettingsDialog::Accept_click()
{
	bdInfo::dataBase = ui.lineEdit->text();
	bdInfo::table = ui.lineEdit_2->text();
	bdInfo::folder = ui.lineEdit_3->text();
	this->close();
}

void SettingsDialog::Cancel_click()
{
	this->close();
}

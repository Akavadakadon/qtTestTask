#pragma once

#include <QDialog>
#include <QObject>
#include "ui_SettingsDialog.h"
#include "model.cpp"

class SettingsDialog : public QDialog
{

public:
	SettingsDialog(QWidget *parent = nullptr);
	~SettingsDialog();

private:
	Ui::SettingsDialogClass ui;

	void Accept_click();
	void Cancel_click();
};

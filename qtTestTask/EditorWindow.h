#pragma once

#include <QDialog>
#include "ui_EditorWindow.h"
#include "model.cpp"


class EditorWindow : public QDialog
{
	Q_OBJECT

public:
	EditorWindow(EditorModel editor, QWidget *parent = nullptr);
	~EditorWindow();
	bool edited;
	EditorModel updatedEditor;
	void ApplyClicked();
	void CancelClicked();
private:
	Ui::EditorWindowClass ui;
};

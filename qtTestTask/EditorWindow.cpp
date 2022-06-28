#include "EditorWindow.h"

EditorWindow::EditorWindow(EditorModel editor, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.lineEdit->setText(editor.texteditor);
	ui.lineEdit_2->setText(editor.fileformats);
	ui.lineEdit_3->setText(editor.encoding);
	ui.lineEdit_4->setText(editor.hasintellisense);
	ui.lineEdit_5->setText(editor.hasplugins);
	ui.lineEdit_6->setText(editor.cancompile);

	connect(ui.pushButton, &QPushButton::clicked, this, &EditorWindow::ApplyClicked);
	connect(ui.pushButton_2, &QPushButton::clicked, this, &EditorWindow::CancelClicked);
}

void EditorWindow::ApplyClicked()
{
	updatedEditor.texteditor = ui.lineEdit->text();
	updatedEditor.fileformats = ui.lineEdit_2->text();
	updatedEditor.encoding = ui.lineEdit_3->text();
	updatedEditor.hasintellisense = ui.lineEdit_4->text();
	updatedEditor.hasplugins = ui.lineEdit_5->text();
	updatedEditor.cancompile = ui.lineEdit_6->text();
	this->close();
}

void EditorWindow::CancelClicked()
{

	this->close();
}

EditorWindow::~EditorWindow()
{}

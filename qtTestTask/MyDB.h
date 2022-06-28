#pragma once
#include <QSql>
#include <QtSql/QSqlDatabase>
#include <QThread>
#include <QList>
#include <String>
#include "model.cpp"


class MyDB : public QObject
{
	Q_OBJECT
private:
	QSqlDatabase db;
	DBinf dbInfo;
public:
	MyDB(DBinf dbInfo);
	MyDB();
	static DBinf LoadFile(QString filePath);
	QList<EditorModel> LoadDefault();
	QList<EditorModel> Load();
	int Connect();

	void Select();//insert
	bool IfExist(EditorModel editor);
	QList<EditorModel> SelectAll();//insert
	void Insert(EditorModel newEditor);//insert Delete Update
	bool Delete(EditorModel editor);
	void Update(EditorModel changedEditor, int col);// 
	void Create(QString table);// Create
	void Close();
signals:
	void DataReady(QList<EditorModel> db);
	EditorModel rmEditor();
	void initiated(QList<EditorModel> db);
	void error(const char* error);
	void ImportSuccessed(QString fileName);
	void ImportFailed(QString fileName, QString error);
};

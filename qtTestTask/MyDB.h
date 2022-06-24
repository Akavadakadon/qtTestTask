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
	static DBinf LoadFile(QString filePath);
	QList<EditorModel> LoadDefault();
	QList<EditorModel> Load();
	int Connect();

	void Select();//insert
	void Insert(EditorModel newEditor);//insert Delete Update
	void Delete();//
	void Update();// 
	void Create(QString table);// Create
signals:
	void afgan();
	void initiated(QList<EditorModel> db);
	void error(const char* error);
};

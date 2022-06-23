#pragma once
#include <QSql>
#include <QtSql/QSqlDatabase>
#include <QThread>
#include <String>

struct DBinf
{
	std::string host;
	std::string dataBase;
	std::string password;
	std::string userName;
	bool login;
};

class DBexception :std::exception
{
private:
	std::string text;
public:
	DBexception(std::string text) :text(text) {}
	const char* what() const override {
		return text.c_str();
	}
};

class MyDB : public QObject
{
	Q_OBJECT
private:
	QSqlDatabase db;
	DBinf dbInfo;
public:
	MyDB(DBinf dbInfo);
	static DBinf LoadFile(std::string filePath);
	int Connect();
signals:
	void error(const char* error);
};

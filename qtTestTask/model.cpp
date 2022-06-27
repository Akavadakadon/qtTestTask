#include <QString>
#pragma once

struct DBinf
{
	QString host;
	QString dataBase;
	QString password;
	QString userName;
	QString table;
	bool login;
};

struct asd
{
	 static QString host ;
	 static QString dataBase;
	 static QString table;
	 static QString folder ;
};

class bdInfo
{
public:
	static QString host;
	static QString dataBase;
	static QString table;
	static QString folder;

	QString getHost() {
		return host;
	}
	QString getDataBase() {
		return dataBase;
	}
	QString getTable() {
		return table;
	}
	QString getFolder() {
		return folder;
	}

	static void setHost(QString val) {
		host = val;
	};
	void setDataBase(QString val) {
		dataBase = val;
	};
	void setTable(QString val) {
		table = val;
	};
	void setFolder(QString val) {
		folder = val;
	};
	bdInfo(int )
	{
	}
};

struct EditorModel
{
	// dbInfo.dataBase
	int id;
	QString texteditor;
	QString fileformats;
	QString encoding;
	QString hasintellisense;
	QString hasplugins;
	QString cancompile;
	int max_size = 6;

	QString get(int a)
	{
		switch (a)
		{
		case 0:
			return texteditor;
		case 1:
			return fileformats;
		case 2:
			return encoding;
		case 3:
			return hasintellisense;
		case 4:
			return hasplugins;
		case 5:
			return cancompile;
		default:
			break;
		}
		return "";
	}

	void set(int a, const QString val)
	{
		switch (a)
		{
		case 0:
			texteditor = val;
			break;
		case 1:
			fileformats = val;
			break;
		case 2:
			encoding = val;
			break;
		case 3:
			hasintellisense = val;
			break;
		case 4:
			hasplugins = val;
			break;
		case 5:
			cancompile = val;
			break;
		default:
			break;
		}
	}
};
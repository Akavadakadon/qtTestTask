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

struct EditorModel
{
	// dbInfo.dataBase
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
			return texteditor;
		case 4:
			return hasintellisense;
		case 5:
			return hasplugins;
		case 6:
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
			texteditor = val;
			break;
		case 4:
			hasintellisense = val;
			break;
		case 5:
			hasplugins = val;
			break;
		case 6:
			cancompile = val;
			break;
		default:
			break;
		}
	}
};
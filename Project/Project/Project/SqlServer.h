#pragma once
#include <QsqlDatabase>
#include <qsqlquery.h>
#include <qsqlrecord.h>
#include <qtextcodec.h>
#include <qmessagebox.h>
#include <qvariant.h>
#include <list>
#include <set>
class SqlServer
{
private:
	SqlServer();
public:
	~SqlServer();
private:
	QSqlDatabase db;
	const QString dsn = QString("Driver={sql server};server=127.0.0.1;database=SensorData;ui=sa;pwd=sj141592");
	static SqlServer *sql;
	QSqlQuery *query;
public:
	/*传感器名字和对应网址*/
	QString _msnu_name;
	QString _msnu_url;
	/*QLabel文本*/
	QString _mwt_qLabelText;
	/*传感器名字*/
	QString _ssn_name;
	/*Data Date*/
	QString _mdd_name;
	QString _mdd_data;
	QString _mdd_date;
private:
	void InitDB();
	inline bool Exec(QString &str);
public:
	std::list<QString> getSnName();
	QString getSnuUrl(QString str);
	std::list<QString> getLabelText();
	std::set<QString> getDdDate();
	std::list<QString> getDdName(QString date);
	QString getDdData(QString name,QString date);
public:
	bool InsertData(QString str);
	bool InsertData(QString str,QString data);
	bool InsertNDD(QString name,QString data,QString date);
public:
	bool DelNameUrl(QString str);
	bool DelDate(QString date);
public:
	static SqlServer * GetInstance() {
		if (sql == nullptr)
			if (sql == nullptr)
				sql = new SqlServer();
		return sql;
	}
};


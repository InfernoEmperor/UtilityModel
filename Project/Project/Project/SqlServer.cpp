#include "SqlServer.h"

SqlServer * SqlServer::sql = nullptr;

SqlServer::SqlServer()
{
	InitDB();
}


SqlServer::~SqlServer()
{
	db.close();
}

void SqlServer::InitDB() {
	db = QSqlDatabase::addDatabase("QODBC");
	db.setDatabaseName(dsn);
	db.setDatabaseName(dsn);
	db.setHostName(QString("127.0.0.1"));
	db.setPort(1433);
	db.setUserName(QString("sa"));
	db.setPassword("sj141592");
	if (!db.open()) {
		QMessageBox::warning(NULL,QObject::tr("Hint"),QObject::tr("DataBase  can\'t Open! Please Check!"));
		return;
	}
	query = new QSqlQuery(db);
}

 bool SqlServer::Exec(QString &str) {
	if (!query->exec(str))
		return false;
	return true;
}
std::list<QString> SqlServer::getSnName() {
	std::list<QString> temp;
	QString sqlState = "select sensor_name from map_sensor_name_url";
	if (!Exec(sqlState))
	{
		QMessageBox::warning(NULL, QObject::tr("Hint"),QObject::tr("sql exec error!"));
		return temp;
	}
	while (query->next()) {
		int num = query->record().indexOf("sensor_name");
		QString name = query->value(num).toString();
		temp.push_back(name);
	}
	return temp;
}
QString SqlServer::getSnuUrl(QString str) {
	QString sqlState = "select sensor_url from map_sensor_name_url where sensor_name=\'"+str+"\'";
	if (!Exec(sqlState))
	{
		QMessageBox::warning(NULL, QObject::tr("Hint"), QObject::tr("sql exec error!"));
		return NULL;
	}
	if (query->first()) {
		int num = query->record().indexOf("sensor_url");
		QString url = query->value(num).toString();
		return url;
	}
	return NULL;
}
std::list<QString> SqlServer::getLabelText() {
	return getSnName();
}
std::set<QString> SqlServer::getDdDate() {
	std::set<QString> tmp;
	QString sql = "select dat from t_sensor_data_date";
	if (!Exec(sql))
	{
		QMessageBox::warning(NULL, QObject::tr("Hint"), QObject::tr("sql exec error!"));
		return tmp;
	}
	while (query->next()) {
		int num = query->record().indexOf("dat");
		QString date = query->value(num).toString();
		tmp.insert(date);
	}
	return tmp;
}

std::list<QString> SqlServer::getDdName(QString date) {
	std::list<QString> tmp;
	QString sql = "select sensor_name from t_sensor_data_date where dat=\'" + date+"\'";
	if (!Exec(sql))
	{
		QMessageBox::warning(NULL, QObject::tr("Hint"), QObject::tr("sql exec error!"));
		return tmp;
	}
	while (query->next()) {
		int num = query->record().indexOf("sensor_name");
		QString name = query->value(num).toString();
		tmp.push_back(name);
	}
	return tmp;
}
QString SqlServer::getDdData(QString name, QString date) {
	QString sqlState = "select sensor_data from t_sensor_data_date where sensor_name=\'" + name + "\'" + "and dat=" +"\'"+ date+"\'";
	if (!Exec(sqlState))
	{
		QMessageBox::warning(NULL, QObject::tr("Hint"), QObject::tr("sql exec error!"));
		return NULL;
	}
	if (query->first()) {
		int num = query->record().indexOf("sensor_data");
		QString data = query->value(num).toString();
		return data;
	}
	return NULL;
}

bool SqlServer::InsertData(QString str) {
	QString sql = "insert into map_sensor_name_url values(\'"+str+"\',"+"\'\')";
	if (!Exec(sql))
	{
		QMessageBox::warning(NULL, QObject::tr("Hint"), QObject::tr("sql exec error!"));
		return false;
	}
	return true;
}
bool SqlServer::InsertData(QString str, QString URL) {

	QString sql = "update map_sensor_name_url set sensor_url=\'" + URL + +"\'"+" where sensor_name=\'" + str+"\'";
	if (!Exec(sql))
	{
			QMessageBox::warning(NULL, QObject::tr("Hint"), QObject::tr("sql exec error!"));
			return false;
	}
	return true;
}

bool SqlServer::InsertNDD(QString name, QString data, QString date) {
	QString sql = "insert into t_sensor_data_date values( \'"  + name + "\'"+ "," + "\'" + data + "\'"+","+"\'" + date + "\'"+")";
	if (!Exec(sql))
	{
		QMessageBox::warning(NULL, QObject::tr("Hint"), QObject::tr("sql exec error!"));
		return false;
	}
	
	return true;
}

bool SqlServer::DelNameUrl(QString str) {
	QString sql = "delete from map_sensor_name_url where sensor_name=\'" + str+"\'";
	if (!Exec(sql))
	{
		QMessageBox::warning(NULL, QObject::tr("Hint"), QObject::tr("sql exec error!"));
		return false;
	}
	return true;
}

bool SqlServer::DelDate(QString date) {
	QString sql = "delete from t_sensor_data_date where dat=\'" + date+"\'";
	if (!Exec(sql))
	{
		QMessageBox::warning(NULL, QObject::tr("Hint"), QObject::tr("sql exec error!"));
		return false;
	}
	return true;
}


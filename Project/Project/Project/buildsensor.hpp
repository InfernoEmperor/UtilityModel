#pragma once
#include <QWidget>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <QtCore>
#include <qtextcodec.h>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <qmessagebox.h>
#include <map>
#include <set>
#include <vector>
#include <qcombobox.h>
#include <qgroupbox.h>
#include "childSensor.h"


class BuildSensor : public QWidget {
	Q_OBJECT

private:
	BuildSensor(QWidget * parent = Q_NULLPTR);
public:
	~BuildSensor();
private:
	/*控件*/
	static BuildSensor *_single_sensor;
	QHBoxLayout *__MdMainLayout;
	//历史
	QPushButton *__His_open;
	QPushButton *__His_del;
	QListWidget *__His_list;
	QWidget		*_child_widget;//弹出新窗口显示数据
	//传感器数据 
	//上行
	QLabel		* _add_Sensor_name;
	QLineEdit	* _new_Sensor_name;
	QPushButton * _add_Sensor;
	QPushButton * _delete_Sensor;
	std::set<std::string> _sensor_set;
	QLabel		* _sensor_name;
	QComboBox	* _sensor;
	QLabel      * _url_name;
	QLineEdit	* _url;
	QPushButton * _url_ok;
	QPushButton * _data_update;
	std::map<std::string, std::string> _sensor_name_url;
	//下行
	std::map<QLabel *, QLineEdit *> _sensor_name_data;
	
	QTimer *timer;//定时器
	size_t _min;//分钟
	const size_t default_min = 5;
	QLabel * _min_label;
	QLineEdit *_min_edit;
	QPushButton *_min_push;
	QPushButton *_min_Open;
	QPushButton *_min_Close;

	QPushButton	* _data_Save;
	QGroupBox	* _container;
	QGridLayout * _ddown;
	const int _max_j = 3;
	size_t _i;
	size_t _j;
	//布局
	QGridLayout * up;
	QGridLayout * down;
	QGridLayout * LeftLayout;
	QVBoxLayout * RightLayout;
	//创建子窗口
	childSensor *_child;
private:
	/*数据变量*/
	//QTextCodec *codec;
	SqlServer *sql;
private slots:
	void AddSensor();
	void DeleteSensor();
	void Btncombo();
	void UrlOk();
	void OpenHis();
	void DeleteHis();
	void DataSave();
	void UpdateData();
	void SetTimer();
private:
	void InitLayout();
	bool LoadData();
	bool LoadListData();
	
	void MinOpen();
	void MinClose();
	void RTimer();
	QByteArray getHtml(QString& url);
	/*bool WriteTmp(QString& content);*/
	bool SetDataToCon(std::pair<QLabel*, QLineEdit*> &p,QByteArray & str);
	inline std::pair<QLabel*, QLineEdit*> BuildContainer(QString str);
public:
	static BuildSensor * GetInstance() {
		if (_single_sensor == nullptr)
			if (_single_sensor == nullptr)
				_single_sensor = new BuildSensor();
		return _single_sensor;
	}
};

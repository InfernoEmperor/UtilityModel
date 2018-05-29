#include "buildsensor.hpp"


BuildSensor* BuildSensor::_single_sensor = nullptr;
BuildSensor::BuildSensor(QWidget * parent) : QWidget(parent) {	
	InitLayout();
	LoadData();
	//codec = QTextCodec::codecForName("utf-8");
	connect(_add_Sensor,SIGNAL(clicked(bool)),SLOT(AddSensor()));
	connect(_delete_Sensor,SIGNAL(clicked(bool)),SLOT(DeleteSensor()));
	connect(_url_ok,SIGNAL(clicked(bool)),SLOT(UrlOk()));
	connect(_sensor,SIGNAL(currentIndexChanged(int)),SLOT(Btncombo()));
	connect(_data_Save, SIGNAL(clicked(bool)), SLOT(DataSave()));
	connect(__His_del, SIGNAL(clicked(bool)), SLOT(DeleteHis()));
	connect(__His_open,SIGNAL(clicked(bool)),SLOT(OpenHis()));
	connect(_min_push,SIGNAL(clicked(bool)),SLOT(SetTimer()));
	connect(_min_Open,SIGNAL(clicked(bool)),SLOT(MinOpen()));
	connect(_min_Close, SIGNAL(clicked(bool)), SLOT(MinClose()));
	connect(_data_update,SIGNAL(clicked(bool)),SLOT(UpdateData()));
	connect(timer, SIGNAL(timeout()), SLOT(RTimer()));
	this->setLayout(__MdMainLayout);

}

BuildSensor::~BuildSensor() {
	try {
		timer->stop();
	}
	catch (...) {}
}

void BuildSensor::InitLayout() {
	__MdMainLayout = new QHBoxLayout();
	__MdMainLayout->setSpacing(10);
	_i = _j = 0;
	//左布局
	LeftLayout = new QGridLayout();
	__His_open = new QPushButton(tr("Open History"));
	__His_del = new QPushButton(tr("Delete History"));
	__His_list = new QListWidget();
	LeftLayout->addWidget(__His_open, 0, 1);
	LeftLayout->addWidget(__His_del, 0, 2);
	LeftLayout->addWidget(__His_list,1,0,1,3);
	__MdMainLayout->addLayout(LeftLayout);
	//中间间隔
	QLabel *tmp = new QLabel();
	tmp->setAutoFillBackground(true);
	tmp->setPalette(Qt::green);
	__MdMainLayout->addWidget(tmp);
	//右布局
	RightLayout = new QVBoxLayout();
	up = new QGridLayout();
	_add_Sensor_name = new QLabel(tr("Input Sensor Name:"));
	_new_Sensor_name = new QLineEdit();
	_new_Sensor_name->setAlignment(Qt::AlignRight);
	_add_Sensor = new QPushButton(tr("Add"));
	_delete_Sensor = new QPushButton(tr("Delete"));
	_sensor_name = new QLabel(tr("Sensor Name:"));
	_sensor = new QComboBox();
	_url_name = new QLabel(tr("Url:"));
	_url = new QLineEdit();
	_url_ok = new QPushButton(tr("OK"));
	_data_update = new QPushButton(tr("Updates"));
	up->addWidget(_add_Sensor_name, 0, 0);
	up->addWidget(_new_Sensor_name, 0, 1,1,3);
	up->addWidget(_add_Sensor, 0, 4);
	up->addWidget(_delete_Sensor,0,5);
	up->addWidget(_sensor_name, 1, 0);
	up->addWidget(_sensor, 1, 1);
	up->addWidget(_url_name, 1, 2);
	up->addWidget(_url, 1, 3);
	up->addWidget(_url_ok, 1, 4);
	up->addWidget(_data_update, 1, 5);
	//间隔
	RightLayout->addLayout(up);
	QLabel *tm = new QLabel;
	tm->setAutoFillBackground(true);
	tm->setPalette(Qt::green);
	tm->setFixedHeight(15);
	//下行
	timer = new QTimer(this);
	_min = default_min;

	down = new QGridLayout();
	_container = new QGroupBox;
	_container->setAutoFillBackground(true);
	//_container->setPalette(Qt::red);
	
	_ddown = new QGridLayout;
	
	_min_label = new QLabel(tr("auto Save time:"));
	_min_edit = new QLineEdit(QString::number(_min));
	_min_edit->setValidator(new QIntValidator(100, 999, this));
	_min_push = new QPushButton(tr("OK"));
	_min_Open = new QPushButton(tr("Start"));
	_min_Open->setEnabled(false);
	_min_Close = new QPushButton(tr("Close"));
	_min_Close->setEnabled(false);
	_ddown->addWidget(_min_label, _i, 0);
	_ddown->addWidget(_min_edit, _i, 1);
	_ddown->addWidget(_min_push, _i, 2);
	_ddown->addWidget(_min_Open, _i, 3);
	_ddown->addWidget(_min_Close, _i, 4);

	_data_Save = new QPushButton(tr("Save"));
	_data_Save->setEnabled(false);
	_ddown->addWidget(_data_Save, _i++, 2 * _max_j - 1);
	for (size_t i = 0; i < _max_j; ++i) {
		auto p = _sensor_name_data.insert({new QLabel,new QLineEdit});
		_ddown->addWidget(p.first->first, _i,_j++);
		p.first->second->setEnabled(false);
		_ddown->addWidget(p.first->second, _i, _j++);
	}
	
	_container->setLayout(_ddown);

	down->addWidget(_container);

	RightLayout->addWidget(tm);
	RightLayout->addLayout(down);
	//添加右布局
	__MdMainLayout->addLayout(RightLayout);
}
QByteArray BuildSensor::getHtml(QString& url) {
	QNetworkAccessManager *manager = new QNetworkAccessManager();
	QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
	QByteArray responseData;
	QEventLoop eventLoop;
	connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
	eventLoop.exec();       //block until finish
	responseData = reply->readAll();
	return responseData;
}

//bool BuildSensor::WriteTmp(QString& content) {
//	
//	return true;
//}

QString DataExtract(QByteArray &str) {
	QJsonParseError json_error;
	QJsonDocument parse_document = QJsonDocument::fromJson(str, &json_error);
	if (json_error.error != QJsonParseError::NoError) return false;
	if (!parse_document.isObject())
		return false;
	QJsonObject obj = parse_document.object();
	if (!obj.contains("value"))
		return false;
	QJsonValue name_value = obj.take("value");
	return QString::number(name_value.toVariant().toDouble());
}

bool BuildSensor::SetDataToCon(std::pair<QLabel*, QLineEdit*> &p,QByteArray & str) {
	/*1.数据检索  JSON数据处理*/
	//DataExtract()函数
	/* 2.数据显示*/
	p.second->setText(DataExtract(str));
	_data_Save->setEnabled(true);
	
	return true;
}
inline std::pair<QLabel*,QLineEdit*> BuildSensor::BuildContainer(QString str) {
	for (auto tmp = _sensor_name_data.begin(); tmp != _sensor_name_data.end();++tmp) {
		if (tmp->first->text() == str) {
			return{tmp->first,tmp->second};
		}
	}
	for (auto tmp = _sensor_name_data.begin(); tmp != _sensor_name_data.end(); ++tmp) {
		if (tmp->first->text().isEmpty()) {
			tmp->first->setText(str);
			return {tmp->first,tmp->second};
		}
	}
	_sensor_name_data.insert(std::make_pair(new QLabel(str),new QLineEdit()));
	auto p = _sensor_name_data.begin();
	for (; p != _sensor_name_data.end();++p) {
		if (p->first->text() == str)
			break;
	}
	_ddown->addWidget(p->first, ++_j > 2*_max_j-1 ? (_j = 0, ++_i) : _i, _j);
	_ddown->addWidget(p->second,_i,++_j);
	p->second->setEnabled(false);
	return {p->first,p->second};
}

void BuildSensor::UrlOk() {
	if (_sensor->currentText().isEmpty()) {
		QMessageBox::warning(this, tr("Warning"), tr("Please input Sensor and Select!"));
		return;
	}
	if (_url->text().isEmpty()) {
		QMessageBox::warning(this,tr("Warning"),tr("Please input URL!"));
		return;
	}	
	_sensor_name_url[_sensor->currentText().toStdString()] = _url->text().toStdString();
	QByteArray content = getHtml(QString(_sensor_name_url[_sensor->currentText().toStdString()].c_str()));
	if (content.isEmpty()) {
		_sensor_name_url[_sensor->currentText().toStdString()] = "";
		QMessageBox::warning(this,tr("Error"),tr("Please input true url! Or Check Network!"));
		_url->clear();
		this->setCursor(_url->cursor());
		return;
	}
	std::pair<QLabel*, QLineEdit*> p = BuildContainer(_sensor->currentText());
	if (!SetDataToCon(p,content)) {
		_sensor_name_url[_sensor->currentText().toStdString()] = "";
		_sensor_name_data.erase(p.first);
		try {
			delete p.first;
			delete p.second;
		}
		catch (...) {}
		QMessageBox::warning(this, tr("Error"), tr("Please input your yeelink url!"));
		_url->clear();
		this->setCursor(_url->cursor());
		return;
	}
	/*写入数据库*/
	if (!(sql->InsertData(_sensor->currentText(), QString(_sensor_name_url[_sensor->currentText().toStdString()].c_str()))))
	{
		QMessageBox::warning(this, tr("Error"), tr("Can\'t write database of sensor url!"));
		return;
	}
}
void BuildSensor::OpenHis() {
	//打开数据表中的数据
	/*1.读数据库  2.初始化子窗口 3.显示数据*/
	if (__His_list->currentItem() == NULL) {
		QMessageBox::warning(this, tr("Waring"),tr("Please select one item!") );
		return;
	}
	QString date = __His_list->currentItem()->text();
	childSensor *w = new childSensor(date);
}
void BuildSensor::DeleteHis() {
	//删除数据表中的数据
	if (__His_list->currentItem() == NULL) {
		QMessageBox::warning(this, tr("Waring"), tr("Please select one item!"));
		return;
	}
	QString date = __His_list->currentItem()->text();
	sql->DelDate(date);
	__His_list->clear();
	LoadListData();

}
bool BuildSensor::LoadListData() {
	std::set<QString> date = sql->getDdDate();
	if (date.begin() == date.end())
		return false;
	for (auto tmp : date)
		__His_list->addItem(tmp);
	return true;
}

void BuildSensor::DataSave() {
	//reflush数据
	__His_list->clear();
	UpdateData();
	//保存到数据库 data数据表
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString(Qt::ISODate);
	std::string date = current_date.toStdString();
	std::replace_if(date.begin(), date.end(), [=](char a) {return !isdigit(a); }, '-');
	for (auto tmp = _sensor_name_data.begin(); tmp != _sensor_name_data.end(); ++tmp) {
		if (!tmp->first->text().isEmpty())
			sql->InsertNDD(tmp->first->text(), tmp->second->text(),QString(date.c_str()));
	}
	//reflush QListWidget
	if (!LoadListData()) {
		QMessageBox::warning(this,tr("Hint"),tr("Reflush Error! Check Database!"));
		return;
	}
}

void BuildSensor::AddSensor() {
	if (_new_Sensor_name->text().isEmpty())
	{
		QMessageBox::warning(this, tr("Hint"), tr("Sensor can't be null!"));
		return;
	}
	if (_sensor_set.end() !=_sensor_set.find(_new_Sensor_name->text().toStdString())){
		QMessageBox::warning(this, tr("Hint"), tr("Already Exits! Operator Error!"));
		return;
	}
	_sensor_set.insert(_new_Sensor_name->text().toStdString());
	_sensor->addItem(QString(_new_Sensor_name->text().toStdString().c_str()));
	_sensor_name_url.insert(std::make_pair(_new_Sensor_name->text().toStdString(),""));
	/*插入数据库*/
	if (!sql->InsertData(_new_Sensor_name->text()))
	{
		QMessageBox::warning(this, tr("Error"), tr("Can\'t write database of sensor name!"));
		return;
	}
}
void BuildSensor::DeleteSensor() {
	if (_new_Sensor_name->text().isEmpty())
	{
		QMessageBox::warning(this, tr("Hint"), tr("Sensor can't be null!"));
		return;
	}
	if (QMessageBox::question(this, tr("Hint"), tr("Are you sure do that ?")) == QMessageBox::No)
		return ;
	auto end = _sensor_set.erase(_new_Sensor_name->text().toStdString());
	if (0 == end) {
		QMessageBox::warning(this, tr("Hint"), tr("Don\'t have this sensor!"));
		return;
	}
	_sensor->removeItem(_sensor->findText(_new_Sensor_name->text()));
	_sensor_name_url.erase(_new_Sensor_name->text().toStdString());
	if (!sql->DelNameUrl(_new_Sensor_name->text()))
		return ;

	for (auto p = _sensor_name_data.begin(); p != _sensor_name_data.end(); ++p) {
		if (p->first->text() == _new_Sensor_name->text())
		{
			p->first->setText("");
			p->second->setText("");
			break;
		}
	}
	_new_Sensor_name->setText("");
	_url->setText("");
	QMessageBox::warning(this,tr("Hint!"),tr("Success!"));
}

void BuildSensor::Btncombo() {
	QString str = _sensor->currentText();
	QString(_sensor_name_url[str.toStdString()].c_str()).isEmpty()?_url->setEnabled(true):(_url->setText(QString(_sensor_name_url[str.toStdString()].c_str())),_url->setEnabled(false));
}

bool BuildSensor::LoadData() {
	/*将数据库中的信息加载到对话框*/
	sql = SqlServer::GetInstance();

	std::list<QString> tt_name = sql->getSnName();
	for (auto tt : tt_name) {
		_sensor_set.insert(tt.toStdString());
		_sensor_name_url.insert({tt.toStdString(),sql->getSnuUrl(tt).toStdString()});
		_sensor->addItem(tt);
	}
	_url->setText(QString(_sensor_name_url[_sensor->currentText().toStdString()].c_str()));
	_url->text().isEmpty() ? _url->setEnabled(true) : _url->setEnabled(false);

	std::list<QString> labeltext = sql->getLabelText();
	for (auto tmp = labeltext.begin(); tmp != labeltext.end(); ++tmp) {
		BuildContainer(*tmp);
	}
	LoadListData();
	return true;
}

void BuildSensor::SetTimer() {
	
	/*if (!(0<_min_edit->text().toInt()&& _min_edit->text().toInt()<100)) {
		QMessageBox::warning(this,tr("Warning"),tr("Please input true number(0-100)!"));
		return;
	}*/
	_min = _min_edit->text().toInt();
	_min_Open->setEnabled(true);
}

void BuildSensor::MinOpen() {
	timer->start(_min * 60 * 1000);
	_min_Close->setEnabled(true);
	_min_Open->setEnabled(false);
}

void BuildSensor::MinClose() {
	timer->stop();
	_min_Close->setEnabled(false);
	_min_Open->setEnabled(true);
}
void BuildSensor::RTimer() {
	DataSave();
}

void BuildSensor::UpdateData() {
	auto tmp = _sensor_name_url.begin();
	while (tmp != _sensor_name_url.end()) {
		for (auto p = _sensor_name_data.begin(); p != _sensor_name_data.end(); ++p) {
			if (tmp->first == p->first->text().toStdString())
				p->second->setText(DataExtract(getHtml(QString(tmp->second.c_str()))));
		}
		++tmp;
	}
}

#include "childSensor.h"


childSensor::childSensor(QString str, QWidget *parent)
	: QWidget(parent)
{
	_main = new QGridLayout();
	_i = _j = 0;
	date = str;
	sql = SqlServer::GetInstance();
	if (!LoadData()) {
		QMessageBox::warning(this,tr("Hint"),tr("Load Data from sql is failure!"));
		return;
	}

	this->setLayout(_main);
	this->setFixedSize(400,300);
	this->setWindowTitle(tr("History"));
	this->show();
}

childSensor::~childSensor()
{

}
void childSensor::SetData(QString &label,QString &data) {
	//qt会在整个窗口析构之前  释放所有new对象
	QLabel *tmp_label = new QLabel(QString(label));
	QLineEdit *tmp_edit = new QLineEdit(QString(data));
	tmp_edit->setEnabled(false);
	_main->addWidget(tmp_label, _j > max_j ? (_j = 0, ++_i) : _i, _j++);
	_main->addWidget(tmp_edit, _i, _j); _j++;
}
bool childSensor::LoadData() {
	std::list<QString> label;
	QString data;
	label = sql->getDdName(date);
	for (auto tmp = label.begin(); tmp != label.end(); ++tmp) {
		data = sql->getDdData(*tmp,date);
		if (data.isEmpty())
			return false;
		SetData(*tmp, data);
	}
	return true;
}

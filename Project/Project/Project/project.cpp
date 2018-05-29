#include "project.h"
#include <iostream>

Project::Project(QWidget *parent)
	: QDialog(parent)
{
	ui->setupUi(this);
	__init_Layout();
	this->setLayout(__Main_Layout);
	MoreThread();
}

Project::~Project()
{
	__cam->deleteLater();
}
void Project::MoreThread() {
	_thread_cam->start();
	_thread_sensor->start();
}

void Project::__init_Layout() {
	__Main_Layout = new QVBoxLayout();
	//摄像头模块
	__cam = BuildCamera::GetInstance();
	__Main_Layout->addWidget(__cam);
	_thread_cam = new QThread(this);
	__cam->moveToThread(_thread_cam);
	//间隔
	QLabel *tmp = new QLabel();
	tmp->setAutoFillBackground(true);
	tmp->setPalette(Qt::green);
	__Main_Layout->addWidget(tmp);
	//传感器数据模块
	__sensor = BuildSensor::GetInstance();
	__Main_Layout->addWidget(__sensor);
	_thread_sensor = new QThread(this);
	__sensor->moveToThread(_thread_sensor);
	//间隔
	QLabel *tmp1 = new QLabel();
	tmp1->setAutoFillBackground(true);
	tmp1->setPalette(Qt::green);
	__Main_Layout->addWidget(tmp1);

	//__Main_Layout->setStretch(0,10);
	//__Main_Layout->setStretch(10, 11);
	//__Main_Layout->setStretch(11, 21);
	//__Main_Layout->setStretch(21, 22);



}



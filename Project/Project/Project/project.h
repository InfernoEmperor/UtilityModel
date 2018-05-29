#ifndef PROJECT_H
#define PROJECT_H

#include <QtWidgets/QDialog>
#include "buildcamera.hpp"
#include "buildsensor.hpp"
#include "ui_project.h"
#include <qthread.h>

class Project : public QDialog
{
	Q_OBJECT
public:
	Project(QWidget *parent = 0);
	~Project();
private:
	//主布局
	QVBoxLayout * __Main_Layout;
	//摄像头
	BuildCamera * __cam;
	QThread * _thread_cam;
	//传感器 
	BuildSensor * __sensor;
	QThread * _thread_sensor;
	//ui界面
	Ui::ProjectClass *ui;
private:
	void __init_Layout();
	void MoreThread();
};

#endif // PROJECT_H

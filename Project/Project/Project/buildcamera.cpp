#include "buildcamera.hpp"
#include <qtranslator.h>

BuildCamera * BuildCamera::_single_cam = nullptr;
BuildCamera::BuildCamera(QWidget * parent) : QWidget(parent) {
	__init_Layout();
	__init_Camera();
	__Load_Pic();
	this->setLayout(__UpMainLayout);
	connect(__Open_cam, SIGNAL(clicked(bool)), SLOT(Open_Cam()));
	connect(__Close_cam, SIGNAL(clicked(bool)), SLOT(Close_Cam()));
	connect(__Take_cam,SIGNAL(clicked(bool)),SLOT(Take_Cam()));
	connect(__Save_cam, SIGNAL(clicked(bool)), SLOT(Save_Cam()));
	connect(__His_open, SIGNAL(clicked(bool)), SLOT(His_Open()));
	connect(__His_del,SIGNAL(clicked(bool)),SLOT(His_Del()));
	connect(_theTimer, SIGNAL(timeout()),SLOT(readFrame()));
	connect(_min_push, SIGNAL(clicked(bool)), SLOT(SetSaveTime()));
}

BuildCamera::~BuildCamera() {
	try {
		delete _theTimer;
	}
	catch (...) {
	
	}
}
void BuildCamera::__init_Layout() {
	//主布局
	__UpMainLayout = new QHBoxLayout();
	//初始化 历史纪录 
	QGridLayout* leftLayout = new QGridLayout();
	__His_open = new QPushButton(tr("Open History"));
	__His_del = new QPushButton(tr("Delete History"));
	__His_list = new QListWidget();
	leftLayout->addWidget(__His_open, 0, 1);
	leftLayout->addWidget(__His_del, 0, 2);
	leftLayout->addWidget(__His_list, 1, 0, 1, 3);
	__UpMainLayout->addLayout(leftLayout);
	//间隔左右布局
	__UpMainLayout->setSpacing(10);
	QLabel *tmp = new QLabel();
	tmp->setAutoFillBackground(true);
	tmp->setPalette(Qt::green);
	__UpMainLayout->addWidget(tmp, 0);
	//初始化视频显示界面
	__Show_label = new QLabel();
	__Show_label->setAutoFillBackground(true);
	__Show_label->setPalette(Qt::blue);
	__Show_label->setScaledContents(true);
	//初始化照片显示界面
	QLabel * _min_label = new QLabel(tr("auto save time:"));
	_min_edit=new QLineEdit(QString::number(_c));
	_min_edit->setValidator(new QIntValidator(100, 999, this));
	_min_push = new QPushButton(tr("OK"));

	__Pic_label = new QLabel();
	__Pic_label->setAutoFillBackground(true);
	__Pic_label->setPalette(Qt::yellow);
	__Pic_label->setScaledContents(true);
	//初始化打开、关闭视频功能
	__Open_cam = new QPushButton(tr("Open video"));
	__Close_cam = new QPushButton(tr("Close video"));
	__Open_cam->setEnabled(true);
	__Close_cam->setEnabled(false);
	//初始化 拍照、保存、
	__Take_cam = new QPushButton(tr("Shoot"));
	__Save_cam = new QPushButton(tr("Save"));
	__Take_cam->setEnabled(false);
	__Save_cam->setEnabled(false);
	//调整右布局
	QGridLayout* rightLayout = new QGridLayout();
	rightLayout->addWidget(__Open_cam, 0, 0);
	rightLayout->addWidget(__Take_cam, 0, 1);
	rightLayout->addWidget(_min_label, 0, 2);
	rightLayout->addWidget(_min_edit, 0, 3);
	rightLayout->addWidget(_min_push, 0, 4);
	rightLayout->addWidget(__Save_cam, 1, 0);
	rightLayout->addWidget(__Close_cam, 1, 1);
	rightLayout->addWidget(__Pic_label, 2, 0, 1, 2);
	rightLayout->addWidget(__Show_label, 1, 2, 2, 3);
	rightLayout->setColumnStretch(0, 4);
	rightLayout->setColumnStretch(4, 12);
	__UpMainLayout->addLayout(rightLayout);
}
void BuildCamera::__init_Camera() {
	_cap = new cv::VideoCapture();
	_theTimer = new QTimer(this);
	Interval_Sec = _c * 60 * 1000;
	Current_Res = Interval_Sec;
	filename = QString("Video");
	_pic_file_prev = new QDir;
	if (!(_pic_file_prev->exists(filename)))
		_pic_file_prev->mkdir(filename);
	_pic_file_prev->setPath(filename);
	_path = _pic_file_prev->currentPath()+"/"+filename + "/";
}
void BuildCamera::__Load_Pic() {
	__His_list->clear();
	QDir dir(_path);
	QStringList filter;
	filter << "*.jpg";
	dir.setNameFilters(filter);
	QList<QFileInfo> * fileInfo = new QList<QFileInfo>(dir.entryInfoList(filter));
	for (size_t i = 0; i < fileInfo->count(); ++i)
	{
		__His_list->insertItem(i, fileInfo->at(i).fileName());
	}
	__His_list->show();
	delete fileInfo;
}
void BuildCamera::His_Open() {
	if(__His_list->currentItem() == NULL) {
		QMessageBox::warning(this,"Please select one item!","Waring");
		return;
	}
	QString picName = __His_list->currentItem()->text();
	QString picPath = _path + picName;
	__Pic_label->setPixmap(picPath);
	__Pic_label->show();
}

void BuildCamera::His_Del() {
	if (__His_list->currentItem() == nullptr) {
		QMessageBox::warning(this, "Please select one item!", "Waring");
		return;
	}
	QString picName = __His_list->currentItem()->text();
	QString picPath = _path + picName;
	QFile::remove(picPath);
	__Load_Pic();
}

void BuildCamera::Open_Cam() {	
	__Open_cam->setEnabled(false);
	__Close_cam->setEnabled(true);
	__Take_cam->setEnabled(true);
	if(!_cap->open(1) )
		_cap->open(0);
	_theTimer->start(30);
}
void BuildCamera::Save_Cam() {
	__Save_cam->setEnabled(false);
	QDateTime current_date_time = QDateTime::currentDateTime();
	QString current_date = current_date_time.toString(Qt::ISODate);
	std::string path = _path.toStdString();
	std::string date = current_date.toStdString();
	std::string tmp;
	std::replace_if(date.begin(), date.end(), [=](char a) {return !isdigit(a); },'_');
	sprintf(const_cast<char*>(tmp.c_str()), "%s.jpg", date.c_str());
	QString temp = QString(path.c_str()) + QString(tmp.c_str());
	cvSaveImage(temp.toStdString().c_str(), &IplImage(Save_frame));
	__Load_Pic();
}

void BuildCamera::Close_Cam() {
	__Close_cam->setEnabled(false);
	__Open_cam->setEnabled(true);
	__Take_cam->setEnabled(false);
	try {
		_theTimer->stop();
		_cap->release();
	}
	catch (...) {}
}

void BuildCamera::Take_Cam() {
	__Save_cam->setEnabled(true);
	Save_frame = _frame;
	QImage img = QImage((const uchar *)(Save_frame.data), Save_frame.cols, Save_frame.rows, Save_frame.cols*Save_frame.channels(), QImage::Format_RGB888);
	__Pic_label->clear();
	__Pic_label->setPixmap(QPixmap::fromImage(img));
}
//定时器中断处理函数
void BuildCamera::readFrame() {
	*_cap >> _frame;
	cv::cvtColor(_frame, _frame, CV_BGR2RGB);
	QImage img = QImage((const uchar *)(_frame.data), _frame.cols, _frame.rows, _frame.cols*_frame.channels(), QImage::Format_RGB888);
	if (Interval_Sec != 0) {
		if ((Current_Res -= 30) == 0) {
			Save_Cam();
			Current_Res = Interval_Sec;
		}
	}
	__Show_label->clear();
	__Show_label->setPixmap(QPixmap::fromImage(img));
}
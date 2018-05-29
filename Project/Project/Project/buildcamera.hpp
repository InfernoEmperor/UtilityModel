#pragma once
#include <QObject>
#include <qlabel.h>
#include <qpushbutton.h>
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp> 
#include <opencv2/core/core.hpp> 
#include <qlistwidget.h>
#include <qlayout.h>
#include <qtimer.h>
#include <qwidget.h>
#include <qdatetime.h>
#include <qdir.h>
#include <algorithm>
#include <qmessagebox.h>
#include <qlineedit.h>

class BuildCamera : public QWidget {
	Q_OBJECT
private:
	BuildCamera(QWidget * parent = Q_NULLPTR);
public:
	~BuildCamera();
private:
	//控件
	QLabel *__Show_label;
	QLabel *__Pic_label;
	QPushButton *__His_open;
	QPushButton *__His_del;
	QListWidget *__His_list;
	QPushButton *__Open_cam;
	QPushButton *__Take_cam;
	QPushButton *__Save_cam;
	QPushButton *__Close_cam;
	QWidget * __Current;
	QHBoxLayout * __UpMainLayout;
	/*视频的操作变量*/
	cv::VideoCapture *_cap;
	cv::Mat _frame;
	cv::Mat Save_frame;
	QTimer *_theTimer;
	QDir * _pic_file_prev;
	
	QString _path;
	QString filename;

	size_t Interval_Sec;
	size_t Current_Res;
	QLineEdit *_min_edit;
	QPushButton *_min_push;
	

	size_t _c = 5;
public:
	static BuildCamera *_single_cam;
private slots:
	void His_Open();
	void His_Del();
    void Open_Cam();
	void Take_Cam();
	void Save_Cam();
	void Close_Cam();
	void readFrame();
private:
	void __init_Layout();
	void __init_Camera();
	void __Load_Pic();
public:
	static BuildCamera* GetInstance() {
		if (_single_cam == nullptr)
			if (_single_cam == nullptr)
				_single_cam = new BuildCamera;
		return _single_cam;
	}
	void SetSaveTime() {
		if (!(0<_min_edit->text().toInt() && _min_edit->text().toInt()<100)) {
			QMessageBox::warning(this, tr("Warning"), tr("Please input number!"));
			return;
		}
		_c = _min_edit->text().toInt();
		Interval_Sec = _c * 60 * 1000;
		Current_Res = Interval_Sec;
	}
};


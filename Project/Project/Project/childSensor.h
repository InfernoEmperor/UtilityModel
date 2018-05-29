#ifndef CHILDSENSOR_H
#define CHILDSENSOR_H

#include <QWidget>
#include <qmessagebox.h>
#include <qlayout.h>
#include <memory>
#include <qlabel.h>
#include <qlineedit.h>
#include "SqlServer.h"

class childSensor : public QWidget
{
public:
	childSensor(QString str, QWidget *parent=NULL);
	~childSensor();
private:
	QGridLayout *_main;
	SqlServer *sql;
private:
	QString date;
	const size_t max_j = 3;
	size_t _i;
	size_t _j;
private:
	bool LoadData();
	void SetData(QString &label, QString &data);
};

#endif // CHILDSENSOR_H

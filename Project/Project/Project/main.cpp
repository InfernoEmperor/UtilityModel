#include "project.h"
#include <QtWidgets/QApplication>
#include <qtextcodec.h>
#include <qtranslator.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec *codec = QTextCodec::codecForName("System");
	QTextCodec::setCodecForLocale(codec);
	//…Ë÷√◊÷ÃÂ
	QFont font("ZYSong18030",12);
	QApplication::setFont(font);
	QTranslator tr(0);
	tr.load("project_zh.ts",".");
	a.installTranslator(&tr);
	Project w;
	w.show();
	return a.exec();
}

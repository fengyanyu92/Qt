#include "QCssTest.h"
#include <QtWidgets/QApplication>
#include <QFile>

#include "UIDef.h"
#include "fontTool.h"

bool initUIStyle(QApplication* a);
bool initFont();


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	if (!initUIStyle(&a))
		QWARNING(QString::fromLocal8Bit("black.css��ʽ�ļ�����ʧ�ܣ�"));

	if (!initFont())
		QWARNING(QString::fromLocal8Bit("����ICON�����ʧ�ܣ�"));
    QCssTest w;
    w.show();
    return a.exec();
}


bool initUIStyle(QApplication* a)
{
	QFile file("./CSS/black.css");
	QString styleSheet = "";
	if (file.open(QFile::ReadOnly))
	{
		styleSheet = QLatin1String(file.readAll());

		a->setStyleSheet(styleSheet);
		file.close();
		return true;
	}
	return false;
}

bool initFont()
{
	return fontTool::service()->addThirdpartyFontLib("./font/iconfont.ttf", fontTool::EFT_Icon);
}
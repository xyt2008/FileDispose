#include "filedispose.h"
#include <QtWidgets/QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

    // 加载翻译文件
    QTranslator translator;
    QString strPath = QApplication::applicationDirPath();
    translator.load(strPath + QDir::separator() + "Resources" + QDir::separator() + "filedispose.qm");
    a.installTranslator(&translator);

	CFileDispose w;
	w.show();
	return a.exec();
}

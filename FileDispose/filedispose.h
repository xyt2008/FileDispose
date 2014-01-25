#ifndef FILEDISPOSE_H
#define FILEDISPOSE_H

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include "ui_filedispose.h"

class CFileDispose : public QMainWindow
{
	Q_OBJECT

public:
	CFileDispose(QWidget *parent = 0);
	~CFileDispose();

private slots:
	// 定义各个槽函数
	// 选择路径
	void slotGetPath();

	// 删除对应字符
	void slotDelete();

private:
	// 初始化界面
	void init();

	// 读取路径下的所有文件并显示在表格中
	void fillTableWidgetWithPath(const QString& strPath);

	// 名字处理函数，删除选定内容
	QString dealWithFileName(const QString& strFileName,
		const QString& strDelContext);

private:
	Ui::FileDispose ui;
	QFileInfoList m_listFileList;
};

#endif // FILEDISPOSE_H

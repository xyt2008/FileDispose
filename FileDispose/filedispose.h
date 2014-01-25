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
	// ��������ۺ���
	// ѡ��·��
	void slotGetPath();

	// ɾ����Ӧ�ַ�
	void slotDelete();

private:
	// ��ʼ������
	void init();

	// ��ȡ·���µ������ļ�����ʾ�ڱ����
	void fillTableWidgetWithPath(const QString& strPath);

	// ���ִ�������ɾ��ѡ������
	QString dealWithFileName(const QString& strFileName,
		const QString& strDelContext);

private:
	Ui::FileDispose ui;
	QFileInfoList m_listFileList;
};

#endif // FILEDISPOSE_H

#include "filedispose.h"
#include "translation.h"

CFileDispose::CFileDispose(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	init();
}

CFileDispose::~CFileDispose()
{

}

void CFileDispose::init()
{
	// �����ź���ۺ���
	connect(ui.pushButtonPath, SIGNAL(pressed()), this, SLOT(slotGetPath()));
	connect(ui.pushButtonDel, SIGNAL(pressed()), this, SLOT(slotDelete()));
	connect(ui.actionExit_Q, SIGNAL(triggered()), this, SLOT(close()));

	// ������һ�������������ʾ����
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);
}

void CFileDispose::slotGetPath()
{
	QString strDir = QFileDialog::getExistingDirectory(this, 
        Q_TRANSF_SELECTDIR, "", QFileDialog::ShowDirsOnly);

	if (!strDir.isEmpty() && QFileInfo::exists(strDir))
	{
		ui.lineEditPath->setText(strDir);
		fillTableWidgetWithPath(strDir);
	}
}

void CFileDispose::slotDelete()
{
	// ��ȡҪɾ��������
	QString strDelContext = ui.lineEditDelContext->text();
	// �ж��Ƿ�Ϊ��
	if (strDelContext.isEmpty())
	{
		// Ϊ����ֱ����ʾ�������
        QMessageBox::information(this, Q_TRANSF_STATUS, Q_TRANSF_SUCCESS);
		return;
	}
	for (int i = 0; i < m_listFileList.size(); ++i)
	{
		// ��ȡ�����ļ���Ϣ
		QFileInfo info = m_listFileList.at(i);
		QFile file(info.filePath());
        file.rename(ui.lineEditPath->text() + QDir::separator()
			+ dealWithFileName(info.fileName(), strDelContext));
	}

    QMessageBox::information(this, Q_TRANSF_STATUS, Q_TRANSF_SUCCESS);

	// ���¶�ȡ�ļ��б�
	fillTableWidgetWithPath(ui.lineEditPath->text());
}

void CFileDispose::fillTableWidgetWithPath(const QString& strPath)
{
	if (!strPath.isEmpty() && QFileInfo::exists(strPath))
	{
		// ����ձ������
		ui.tableWidget->setRowCount(0);
		m_listFileList.clear();

		QDir dir;
		dir.setPath(strPath);

		// ��ȡĿ¼�������ļ�
		m_listFileList = dir.entryInfoList(QDir::Files | QDir::NoDot | QDir::NoDotDot);
		for (int i = 0; i < m_listFileList.size(); ++i)
		{
			// ����һ�б�������
			ui.tableWidget->insertRow(i);

			// ��ȡ�����ļ���Ϣ
			QFileInfo info = m_listFileList.at(i);

			// ���ļ�����䵽����0��
			QTableWidgetItem* pItem = new QTableWidgetItem;
			pItem->setText(info.fileName());
			ui.tableWidget->setItem(i, 0, pItem);

			// ���ļ�·����䵽����1��
			pItem = new QTableWidgetItem;
			pItem->setText(info.filePath());
			ui.tableWidget->setItem(i, 1, pItem);
		}
	}
}

QString CFileDispose::dealWithFileName(const QString& strFileName,
									   const QString& strDelContext)
{
	QString strName = strFileName;
	if (strName.isEmpty() || strDelContext.isEmpty())
	{
		return "";
	}

	while (true)
	{
		// ѭ������Ҫɾ������
		int nPos = strName.indexOf(strDelContext);
		if (nPos > -1)
		{
			strName.replace(nPos, strDelContext.length(), "");
			continue;
		}
		// �������˳�ѭ��
		break;
	}

	return strName;
}

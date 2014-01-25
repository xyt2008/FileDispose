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
	// 连接信号与槽函数
	connect(ui.pushButtonPath, SIGNAL(pressed()), this, SLOT(slotGetPath()));
	connect(ui.pushButtonDel, SIGNAL(pressed()), this, SLOT(slotDelete()));
	connect(ui.actionExit_Q, SIGNAL(triggered()), this, SLOT(close()));

	// 表格最后一行填充满整个显示区域
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
	// 获取要删除的内容
	QString strDelContext = ui.lineEditDelContext->text();
	// 判断是否为空
	if (strDelContext.isEmpty())
	{
		// 为空则直接提示任务完成
        QMessageBox::information(this, Q_TRANSF_STATUS, Q_TRANSF_SUCCESS);
		return;
	}
	for (int i = 0; i < m_listFileList.size(); ++i)
	{
		// 获取具体文件信息
		QFileInfo info = m_listFileList.at(i);
		QFile file(info.filePath());
        file.rename(ui.lineEditPath->text() + QDir::separator()
			+ dealWithFileName(info.fileName(), strDelContext));
	}

    QMessageBox::information(this, Q_TRANSF_STATUS, Q_TRANSF_SUCCESS);

	// 重新读取文件列表
	fillTableWidgetWithPath(ui.lineEditPath->text());
}

void CFileDispose::fillTableWidgetWithPath(const QString& strPath)
{
	if (!strPath.isEmpty() && QFileInfo::exists(strPath))
	{
		// 先清空表格内容
		ui.tableWidget->setRowCount(0);
		m_listFileList.clear();

		QDir dir;
		dir.setPath(strPath);

		// 获取目录下所有文件
		m_listFileList = dir.entryInfoList(QDir::Files | QDir::NoDot | QDir::NoDotDot);
		for (int i = 0; i < m_listFileList.size(); ++i)
		{
			// 增加一行报个内容
			ui.tableWidget->insertRow(i);

			// 获取具体文件信息
			QFileInfo info = m_listFileList.at(i);

			// 把文件名填充到表格第0列
			QTableWidgetItem* pItem = new QTableWidgetItem;
			pItem->setText(info.fileName());
			ui.tableWidget->setItem(i, 0, pItem);

			// 把文件路径填充到表格第1列
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
		// 循环查找要删除内容
		int nPos = strName.indexOf(strDelContext);
		if (nPos > -1)
		{
			strName.replace(nPos, strDelContext.length(), "");
			continue;
		}
		// 不存则退出循环
		break;
	}

	return strName;
}

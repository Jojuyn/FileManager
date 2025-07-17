#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <QObject>
#include <QString>
#include <QFileInfo>
#include <QDateTime>
#include <QFileDevice>
#include <QVariantMap>

/**
 * @brief 文件操作综合类
 * 整合基础文件操作、属性管理和回收站功能
 */
class FileOperations : public QObject
{
	Q_OBJECT
public:
	explicit FileOperations(QObject *parent = nullptr);

	// ================= 基础文件操作 =================
	bool createFile(const QString &filePath, const QString &content = "");
	bool createDirectory(const QString &dirPath);
	bool deleteFile(const QString &filePath, bool permanent = false);
	bool deleteDirectory(const QString &dirPath, bool permanent = false);
	bool rename(const QString &oldPath, const QString &newName);
	bool copy(const QString &source, const QString &destination);
	bool move(const QString &source, const QString &destination);

	// ================= 属性管理（整合组员代码） =================
	static QVariantMap getFileProperties(const QString &path);
	static bool setFileModifiedTime(const QString &path, const QDateTime &time);

	// ================= 回收站操作 =================
	bool moveToRecycleBin(const QString &path);
	bool restoreFromRecycleBin(const QString &path);
	bool emptyRecycleBin();

	signals:
		void operationCompleted(const QString &operation, bool success);
	void errorOccurred(const QString &errorMessage);

private:
	// 平台相关的私有方法
	bool nativeMoveToTrash(const QString &path);
	bool nativeRestoreFromTrash(const QString &path);
};

#endif // FILEOPERATIONS_H
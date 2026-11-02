/* Copyright (c) 2026 GBAx contributors
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. See http://mozilla.org/MPL/2.0/. */
#include "platform/qt/LauncherData.h"

#include <QTemporaryDir>
#include <QTest>

class LauncherDataTest : public QObject {
Q_OBJECT
private slots:
 void atomicWriteAndFailure() {
  QTemporaryDir dir;
  const QString path = dir.filePath("metadata.json");
  QVERIFY(QGBA::writeLauncherData(path, "old"));
  { QSaveFile interrupted(path); QVERIFY(interrupted.open(QIODevice::WriteOnly)); interrupted.write("partial"); interrupted.cancelWriting(); }
  QFile read(path); QVERIFY(read.open(QIODevice::ReadOnly)); QCOMPARE(read.readAll(), QByteArray("old")); read.close();
  QVERIFY(QGBA::writeLauncherData(path, "new"));
  QVERIFY(read.open(QIODevice::ReadOnly)); QCOMPARE(read.readAll(), QByteArray("new"));
  QVERIFY(QDir().mkpath(dir.filePath("directory")));
  QVERIFY(!QGBA::writeLauncherData(dir.filePath("directory"), "bad"));
  QVERIFY(!QGBA::writeLauncherData(QString(), "bad"));
 }

	void resetPreservesPortableFiles() {
		QTemporaryDir dir;
		QVERIFY(dir.isValid());
		const QStringList preserved = {"GBAx.exe", "portable.ini", "game.gba", "game.sav", "game.ss1", "notes.txt", "artwork/cache/cover.png", "roms/game.gba"};
		const QStringList removed = {"config.ini", "qt.ini", "library-cache.json", "gbax-installed-links.json", "gbax-hidden-installed.json", "library.sqlite3", "library.sqlite3-wal", "library.sqlite3-shm"};
		for (const QString& name : preserved + removed) {
			const QString path = dir.filePath(name);
			QVERIFY(QDir().mkpath(QFileInfo(path).absolutePath()));
			QFile file(path);
			QVERIFY(file.open(QIODevice::WriteOnly));
			QCOMPARE(file.write("unchanged"), qint64(9));
		}
		QVERIFY(QGBA::resetLauncherData(dir.path()));
		for (const QString& name : preserved) {
			QFile file(dir.filePath(name));
			QVERIFY2(file.open(QIODevice::ReadOnly), qPrintable(name));
			QCOMPARE(file.readAll(), QByteArray("unchanged"));
		}
		for (const QString& name : removed) QVERIFY(!QFileInfo::exists(dir.filePath(name)));
		QVERIFY(QGBA::resetLauncherData(dir.path()));
	}

	void resetDoesNotRecurseIntoUnexpectedDirectory() {
		QTemporaryDir dir;
		QVERIFY(QDir().mkpath(dir.filePath("config.ini")));
		QFile file(dir.filePath("config.ini/game.sav"));
		QVERIFY(file.open(QIODevice::WriteOnly));
		file.write("save");
		file.close();
		QVERIFY(!QGBA::resetLauncherData(dir.path()));
		QVERIFY(file.exists());
	}

	void emptyPathRejected() {
		QVERIFY(!QGBA::resetLauncherData(QString()));
	}
};

QTEST_APPLESS_MAIN(LauncherDataTest)
#include "launcherdata.moc"

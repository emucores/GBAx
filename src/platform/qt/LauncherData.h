/* Copyright (c) 2026 GBAx contributors
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. See http://mozilla.org/MPL/2.0/. */
#pragma once

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QSaveFile>
#include <QStringList>

namespace QGBA {

// Commit a complete replacement or retain the previous file. Never fall back to
// truncating the destination when a temporary file cannot be created.
inline bool writeLauncherData(const QString& path, const QByteArray& payload) {
 if (path.isEmpty() || !QDir().mkpath(QFileInfo(path).absolutePath())) return false;
 QSaveFile file(path);
 file.setDirectWriteFallback(false);
 if (!file.open(QIODevice::WriteOnly)) return false;
 if (file.write(payload) != payload.size()) { file.cancelWriting(); return false; }
 return file.commit();
}

// Portable configurations may share a directory with the executable, ROMs,
// saves and user files. Never recursively delete that directory to reset.
inline bool resetLauncherData(const QString& configDir) {
	if (configDir.isEmpty()) {
		return false;
	}
	const QDir root(configDir);
	const QStringList files = {
		QStringLiteral("config.ini"), QStringLiteral("qt.ini"),
		QStringLiteral("library-cache.json"),
		QStringLiteral("gbax-installed-links.json"),
		QStringLiteral("gbax-hidden-installed.json"),
		QStringLiteral("library.sqlite3"), QStringLiteral("library.sqlite3-wal"),
		QStringLiteral("library.sqlite3-shm")
	};
	for (const QString& name : files) {
		const QString path = root.filePath(name);
		const QFileInfo info(path);
		if ((info.exists() || info.isSymLink()) && !QFile::remove(path)) {
			return false;
		}
	}
	return true;
}

}

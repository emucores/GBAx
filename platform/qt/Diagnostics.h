/* Copyright (c) 2026 GBAx contributors
 * SPDX-License-Identifier: MPL-2.0 */
#pragma once
#include "ConfigController.h"
#include <gbax/core/version.h>
#include <QApplication>
#include <QClipboard>
#include <QSysInfo>
#include <QStringList>
namespace QGBA {
inline QString gbaxDiagnostics(ConfigController* config) {
 QStringList lines{QStringLiteral("GBAx 2.0.0 Preview 2"), QString("Build: %1 (%2)").arg(QString::fromUtf8(projectVersion), QString::fromUtf8(gitCommit)), QString("OS: %1").arg(QSysInfo::prettyProductName()), QString("Architecture: %1").arg(QSysInfo::currentCpuArchitecture()), QString("Qt: %1; window system: %2").arg(qVersion(), QGuiApplication::platformName())};
 if (config) {
  for (const QString& key : {QStringLiteral("displayDriver"), QStringLiteral("audioDriver")}) {
   bool ok = false; int value = config->getQtOption(key).toInt(&ok);
   lines << QString("Configured %1: %2").arg(key, ok ? QString::number(value) : QStringLiteral("default"));
  }
 }
 lines << "No ROM paths, filenames, save contents or personal configuration included.";
 return lines.join("\n");
}
}

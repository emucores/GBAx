/* Copyright (c) 2013-2015 Jeffrey Pfau
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "AboutScreen.h"

#include <gbax/core/version.h>

#include <QFile>
#include <QGuiApplication>
#include <QPixmap>
#include <QScrollArea>
#include <QScreen>
#include <QVBoxLayout>

using namespace QGBA;

AboutScreen::AboutScreen(QWidget* parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint)
{
	m_ui.setupUi(this);

	QPixmap logo(":/res/gbax-logo-tagline.png");
	logo = logo.scaled(m_ui.logo->minimumSize() * devicePixelRatio(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	logo.setDevicePixelRatio(devicePixelRatio());
	m_ui.logo->setPixmap(logo);

	QLatin1String tree(gitBranch);
	if (tree == QLatin1String("(unknown)") || tree == QLatin1String("release")) {
		tree = QLatin1String("release");
	}

	QFile patronFile(":/res/patrons.txt");
	QStringList patronList;
	patronFile.open(QIODevice::ReadOnly | QIODevice::Text);
	while (true) {
		QByteArray line = patronFile.readLine();
		if (line.isEmpty()) {
			break;
		}
		patronList.append(QString::fromUtf8(line).trimmed());
	}

	m_ui.projectName->setText(QLatin1String(projectName));
	m_ui.projectVersion->setText(tr("Version %1").arg(QLatin1String(projectVersion)));

	{
		QString gitInfo = m_ui.gitInfo->text();
		gitInfo.replace("{gitBranch}", QLatin1String(gitBranch));
		gitInfo.replace("{gitCommit}", QLatin1String(gitCommit));
		m_ui.gitInfo->setText(gitInfo);

	}

	{
		QString description = QStringLiteral("GBAx is an open-source Game Boy Advance emulator with a built-in game launcher and library management, based on mGBA.");
		m_ui.description->setText(description);
	}

	{
		QString extraLinks = m_ui.extraLinks->text();
		extraLinks.replace("{gitBranch}", tree);
		m_ui.extraLinks->setText(extraLinks);
	}

	{
		QString patronsHeader = m_ui.patronsHeader->text();
		patronsHeader.replace("{projectName}", QLatin1String(projectName));
		m_ui.patronsHeader->setText(patronsHeader);
	}

	{
		QString patrons = m_ui.patrons->text();
		patrons.replace("{patrons}", patronList.join(" • "));
		m_ui.patrons->setText(patrons);
	}


	m_ui.patronsHeader->setVisible(true);
	m_ui.patronsHeader->setText(QStringLiteral("Release Notes"));
	m_ui.patrons->setVisible(true);
	m_ui.patrons->setText(QStringLiteral("<b>GBAx 2.0.0 Preview 3</b><br/><br/>This preview improves library data safety, save-state controls and smaller-window layouts.<br/><br/><b>Library</b><br/>Metadata and library-link files use atomic replacement. Locate Missing Game can repair favourites, history and statistics after a file moves. Original game and save files are left in place.<br/><br/><b>Gameplay</b><br/>Quick Menu offers state slots 1–9 with stored timestamps, operation feedback, save-file information and a folder shortcut. Continue From State is distinguished from a normal Start Game.<br/><br/><b>Diagnostics</b><br/>Copy version, system and backend information without ROM paths or save contents. Review the report before sharing.<br/><br/><b>Preview Status</b><br/>Hardware coverage, controller reconnect and sleep/wake still need testing across supported systems. Back up your saves before upgrading. Check each download for its requirements and signing status.<br/><br/><b>Project Credits</b><br/>GBAx builds on mGBA and its contributors. Upstream licence notices remain included. Visit https://gbax-emulator.com for documentation and support."));
	m_ui.patrons->setTextFormat(Qt::RichText);
	m_ui.patrons->setWordWrap(true);
	m_ui.patrons->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::LinksAccessibleByMouse);

	m_ui.copyright->setText(QString::fromUtf8("© 2026 GBAx, licensed under the Mozilla Public License, version 2.0. Game Boy Advance is a registered trademark of Nintendo Co., Ltd."));
	m_ui.copyright->setVisible(true);

	// Make the lower release notes area properly scroll on smaller screens.
	if (m_ui.gridLayout_2) {
		m_ui.gridLayout_2->removeWidget(m_ui.patronsHeader);
		m_ui.gridLayout_2->removeWidget(m_ui.patrons);
		m_ui.gridLayout_2->removeWidget(m_ui.copyright);

		auto* notesContainer = new QWidget(this);
		auto* notesLayout = new QVBoxLayout(notesContainer);
		notesLayout->setContentsMargins(8, 0, 8, 0);
		notesLayout->setSpacing(10);
		notesLayout->addWidget(m_ui.patronsHeader);
		notesLayout->addWidget(m_ui.patrons);
		notesLayout->addWidget(m_ui.copyright);
		notesLayout->addStretch(1);

		auto* notesScroll = new QScrollArea(this);
		notesScroll->setObjectName(QStringLiteral("aboutNotesScroll"));
		notesScroll->setWidgetResizable(true);
		notesScroll->setFrameShape(QFrame::NoFrame);
		notesScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		notesScroll->setWidget(notesContainer);
		m_ui.gridLayout_2->addWidget(notesScroll, 6, 0, 3, 2);
	}

	if (m_ui.gridLayout_2) {
		m_ui.gridLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
	}
	setSizeGripEnabled(true);
	setMinimumSize(320, 280);
	resize(980, 720);
	if (QScreen* screen = QGuiApplication::primaryScreen()) {
		const QRect avail = screen->availableGeometry();
		resize(qMin(width(), int(avail.width() * 0.88)), qMin(height(), int(avail.height() * 0.88)));
		move(avail.center() - rect().center());
	}
}
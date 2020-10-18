/*
 * SPDX-FileCopyrightText: 2020 Vlad Zahorodnii <vlad.zahorodnii@kde.org>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <QCoreApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QDebug>
#include <QFileInfo>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("VideoWall");
    QCoreApplication::setApplicationVersion("1.0");
    return 0;
}

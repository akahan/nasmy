/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2015  Roman Yusufkhanov <r.yusufkhanov@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef NASMY_H
#define NASMY_H

#include "mainwindow.h"
#include "project/projectscontroller.h"
#include "editor/filescontroller.h"

#include <QMessageBox>
#include <QApplication>
#include <QObject>

class QWidget;

#define AppName qApp->applicationDisplayName()
#define MsgButton QMessageBox::StandardButton
#define MsgButtons QMessageBox::StandardButtons

namespace Nasmy {
    extern MainWindow* nasmy_ui;

    MainWindow* mainwindow();
    ProjectsController* pc();
    FilesController* fc();

    MsgButton question( const QString& text,
        MsgButtons buttons = MsgButtons(QMessageBox::Yes | QMessageBox::No),
        MsgButton defaultButton = QMessageBox::NoButton );
    MsgButton warning( const QString& text,
        MsgButtons buttons = QMessageBox::Ok,
        MsgButton defaultButton = QMessageBox::NoButton );
    MsgButton critical( const QString& text,
        MsgButtons buttons = QMessageBox::Ok,
        MsgButton defaultButton = QMessageBox::NoButton );
    MsgButton information( const QString& text,
        MsgButtons buttons = QMessageBox::Ok,
        MsgButton defaultButton = QMessageBox::NoButton );
}

#endif // NASMY_H

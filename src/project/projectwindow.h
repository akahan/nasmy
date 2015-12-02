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

#ifndef PROJECTWINDOW_H
#define PROJECTWINDOW_H

#include <QDialog>

#include "ui_projectwindow.h"

class Project;

class ProjectWindow : public QDialog, private Ui::ProjectWindow {
    Q_OBJECT
    public:
        explicit ProjectWindow( QWidget* parent, Project* project = NULL );
        ~ProjectWindow();

        QString const exec_and_return_path();

    private slots:
        void on_nameEdit_textChanged( const QString& );
        void on_buttonBox_accepted();
        void on_buttonBox_rejected();

    private:
        void readProject();
        void saveProject();
};

#endif // PROJECTWINDOW_H

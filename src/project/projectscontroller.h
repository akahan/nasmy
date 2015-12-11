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

#ifndef PROJECTSCONTROLLER_H
#define PROJECTSCONTROLLER_H

#include "project.h"
#include <QObject>

typedef QList<Project*> ProjectsList;

class File;

class ProjectsController : public QObject {
    Q_OBJECT

    public:
        ProjectsController(QObject* parent = 0);

        Project* loadProject( const QString& absolute_path );
        Project* getProject( const QString& absolute_path );
        Project* getProject( const File* file );

        inline Project* activeProject() const { return m_active_project; };

    signals:
        void projectLoaded(Project*);
        void projectActivated(Project*);

    private:
        ProjectsList projectsList;
        Project* m_active_project;
};

#endif // PROJECTSCONTROLLER_H

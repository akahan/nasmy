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

#include "projectscontroller.h"
#include "projectscontroller.h"
#include "nasmy.h"
#include "editor/file.h"

#include <QFileInfo>

ProjectsController::ProjectsController(QObject* parent) : QObject(parent) {

}

Project * ProjectsController::loadProject( const QString& absolute_path ) {
    Q_ASSERT( !absolute_path.isEmpty() );

    Project* p = getProject(absolute_path);

    if (p)
        return p;

    try {
        p = new Project( this, absolute_path );
        p->open();
        projectsList.append( p );
    }
    catch ( const QString& e ) {
        if ( p ) delete p;

        Nasmy::warning( tr( "Error reading project %1:\n%2." ).arg( absolute_path ).arg( e ) );
        return NULL;
    }

    emit projectLoaded(p);

    m_active_project = p;
    emit projectActivated(p);

    return p;
}

Project* ProjectsController::getProject( const QString& absolute_path ) {
    foreach( Project* p, projectsList ) {
        if ( p->absolutePath() == absolute_path ) {
            return p;
        }
    }
    return NULL;
}

Project * ProjectsController::getProject( const File* file ) {
    foreach( Project* p, projectsList ) {
        foreach( const QString& rel_path, p->files() ) {
            QFileInfo file_info(p->projectFolder(), rel_path);
            if ( file->absolutePath() == file_info.absoluteFilePath() ) {
                return p;
            }
        }
    }
    return NULL;
}

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

#include "filescontroller.h"
#include "nasmy.h"
#include "asmedit.h"
#include "mainwindow.h"

FilesController::FilesController(QObject* parent) : QObject(parent) {

}

File* FilesController::loadFile( const QString& absolute_path ) {
    File* file = NULL;

    try {
        file = new File( this, absolute_path );
        if ( !absolute_path.isEmpty() ) {
            file->open();
        }
        filesList.append( file );

        file->m_project = Nasmy::pc()->getProject(file);
    }
    catch ( QString e ) {
        if( file ) delete file;
        Nasmy::warning( tr( "Error reading file %1:\n%2." ).arg( absolute_path ).arg( e ) );
        return NULL;
    }

    emit fileLoaded(file);

    return file;
}

File* FilesController::getFile(const int index) {
    return filesList.at( index );
}

File* FilesController::getFile(const QString& absolute_path) {
    foreach( File* file, filesList ) {
        if ( file->absolutePath() == absolute_path ) {
            return file;
        }
    }
    return NULL;
}

void FilesController::unloadFile(const int index) {
    File* file = getFile(index);
    file->disconnect();
    file->deleteLater();
    filesList.removeAt( index );
}

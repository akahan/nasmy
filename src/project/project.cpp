/*
 * <one line to give the program's name and a brief idea of what it does.>
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

#include "project.h"
#include "nasmy.h"

#include <QSettings>
#include <QObject>

Project::Project( QObject* parent, QString absolute_path ) : QObject( parent ), m_absolute_path( absolute_path ) {
    Q_ASSERT( !absolute_path.isEmpty() );
    m_project_folder = QFileInfo(m_absolute_path).absoluteDir();
}

Project::~Project() {}

void Project::open() {
    QSettings settings( m_absolute_path, QSettings::NativeFormat );

    settings.beginGroup( "project" );
    m_name = settings.value( "name" ).toString();
    m_arch_id = settings.value( "arch_id" ).toInt();
    m_assembly_options = settings.value( "assembly_options" ).toString();
    m_linking_options = settings.value( "linking_options" ).toString();
    m_verbose_build = settings.value( "verbose_build" ).toBool();
    settings.endGroup();

    int size = settings.beginReadArray( "targets" );
    for ( int i = 0; i < size; ++i ) {
        settings.setArrayIndex( i );

        ProjectTarget target;
        target.is_main = settings.value( "is_main" ).toBool();
        target.name = settings.value( "name" ).toString();
        target.files = settings.value( "files" ).toStringList();
        m_targets.append( target );
        m_files.append( target.files );
    }
    settings.endArray();
}

/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2015  <copyright holder> <email>
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
#include <QSettings>
#include <QObject>
#include <QTreeWidgetItem>
#include <QDir>
#include <functional>

#include "nasmy.h"

Project::Project( QObject* parent, QString absolute_path ) : QObject( parent ), absolute_path( absolute_path ) {
    Q_ASSERT( !absolute_path.isEmpty() );
}

Project::~Project() {}

void Project::open() {
    ProjectsTree* projectsTree = Nasmy::mainwindow()->projectsTree;

//     Nasmy::mainwindow()->projectsTree->clear();

    QSettings settings( absolute_path, QSettings::NativeFormat );
    settings.beginGroup( "project" );
    project_name = settings.value( "name" ).toString();
    arch_id = settings.value( "arch_id" ).toInt();
    assembly_options = settings.value( "assembly_options" ).toString();
    linking_options = settings.value( "linking_options" ).toString();
    verbose_build = settings.value( "verbose_build" ).toBool();
    settings.endGroup();

    QTreeWidgetItem* project_item = projectsTree->addProjectItem(project_name);

    int size = settings.beginReadArray( "targets" );
    for ( int i = 0; i < size; ++i ) {
        settings.setArrayIndex( i );
        ProjectTarget target;
        target.name = settings.value( "name" ).toString();
        target.files = settings.value( "files" ).toStringList();
        targets.append( target );
        files.append( target.files );

        QTreeWidgetItem* target_item = projectsTree->addTargetItem(target.name, project_item);
        foreach(const QString& file, target.files ) {
            Nasmy::mainwindow()->projectsTree->addTargetSourceItem(file, target_item);
        }
    }
    settings.endArray();

    std::function<void (const QString&, QTreeWidgetItem*)> list_recursive = [&] (const QString& s_dir, QTreeWidgetItem* folder) {
        QDir dir( s_dir );
        dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
        for ( auto file : dir.entryInfoList() ) {
            if (file.isDir()) {
                QTreeWidgetItem* folder_item = projectsTree->addFolderItem(file.fileName(), project_item);
                list_recursive(file.filePath(), folder_item);
            }
            else if (file.suffix() != "nasmy") {
                projectsTree->addFileItem(file.fileName(), folder);
            }
        }
    };
    list_recursive( QFileInfo(absolute_path).absoluteDir().absolutePath(), project_item );
}

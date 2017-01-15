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

#include "projectstree.h"
#include "projectstreeitem.h"
#include "project.h"
#include "mainwindow.h"

// #include <QFileInfo>

ProjectsTree::ProjectsTree( QWidget* parent ) : QTreeWidget( parent ) {
    setColumnCount(2);
    header()->setMinimumSectionSize(20);
    header()->setStretchLastSection(false);
    header()->setSectionResizeMode(0, QHeaderView::Stretch);
    header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
//     header()->resizeSection(1, 26);
}

ProjectItem * ProjectsTree::addProjectItem(Project* project) {
    ProjectItem* target = new ProjectItem( this, project );
    target->setData( 0, Qt::UserRole, QVariant::fromValue(project) );
    addTopLevelItem( target );
    return target;
}

TargetItem * ProjectsTree::addTargetItem( ProjectItem* project_item, const ProjectTarget& project_target ) {
    TargetItem* target = new TargetItem( project_item, project_target );
    addTopLevelItem( target );
    return target;
}

TargetSourceItem* ProjectsTree::addTargetSourceItem( TargetItem* target, const QFileInfo& file_info ) {
    TargetSourceItem* file = new TargetSourceItem( target, file_info );
    addTopLevelItem( file );
    return file;
}

FolderItem * ProjectsTree::addFolderItem( ProjectBaseItem* parent, const QFileInfo& file_info ) {
    FolderItem* folder = new FolderItem( parent, file_info );
    addTopLevelItem( folder );
    return folder;
}

SourceItem * ProjectsTree::addSourceItem( ProjectBaseItem* folder, const QFileInfo& file_info ) {
    SourceItem* file = new SourceItem( folder, file_info );
    addTopLevelItem( file );
    return file;
}

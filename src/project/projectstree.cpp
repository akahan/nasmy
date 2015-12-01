/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2015  Roman Yusufkhanov r.yusufkhanov@gmail.com
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
#include "mainwindow.h"

ProjectsTree::ProjectsTree( QWidget* parent ) : QTreeWidget( parent ) {
    setColumnCount(2);
    header()->setMinimumSectionSize(20);
    header()->setStretchLastSection(false);
    header()->setSectionResizeMode(0, QHeaderView::Stretch);
    header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
//     header()->resizeSection(1, 26);
}

QTreeWidgetItem * ProjectsTree::addProjectItem(const QString& name) {
    QTreeWidgetItem* target = new ProjectItem( this, name );
    addTopLevelItem( target );
    return target;
}

QTreeWidgetItem * ProjectsTree::addTargetItem( const QString& name, QTreeWidgetItem* parent ) {
    QTreeWidgetItem* target = new TargetItem( parent, name );
    addTopLevelItem( target );
    return target;
}

QTreeWidgetItem * ProjectsTree::addFolderItem( const QString& name, QTreeWidgetItem* parent ) {
    QTreeWidgetItem* folder = new FolderItem( parent, name );
    addTopLevelItem( folder );
    return folder;
}

QTreeWidgetItem* ProjectsTree::addTargetSourceItem( const QString& name, QTreeWidgetItem* target ) {
    QTreeWidgetItem* file = new FileItem( target, name );
    addTopLevelItem( file );
    return file;
}

QTreeWidgetItem * ProjectsTree::addFileItem( const QString& name, QTreeWidgetItem* folder ) {
    QTreeWidgetItem* file = new FileItem( folder, name );
    addTopLevelItem( file );
    return file;
}

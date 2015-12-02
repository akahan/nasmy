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

#include "projectstreeitem.h"
#include "project.h"

ProjectItem::ProjectItem( QTreeWidget* parent, Project* project ) : QTreeWidgetItem( parent ), m_project( project ) {
    setFlags( Qt::ItemIsSelectable | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled );
    setText( 0, project->name() );

    QIcon icon;
    icon.addFile( QStringLiteral( ":/resources/images/target.svg" ), QSize(), QIcon::Normal, QIcon::On );
    setIcon( 0, icon );

    setSizeHint(0, QSize(0, 20));
}


TargetItem::TargetItem( QTreeWidgetItem* parent, const QString& name ) : QTreeWidgetItem( parent ) {
    setFlags( Qt::ItemIsSelectable | Qt::ItemIsDropEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled );
    setText( 0, name );

    setCheckState(1, Qt::Checked);

    QIcon icon;
    icon.addFile( QStringLiteral( ":/resources/images/target.svg" ), QSize(), QIcon::Normal, QIcon::On );
    setIcon( 0, icon );

    QFont font_target( font( 0 ) );
    font_target.setBold( true );
    //     font_target.setItalic(true);
    //     font_target.setWeight(75);
    setFont( 0, font_target );
}

FolderItem::FolderItem( QTreeWidgetItem* parent, const QString& name ) : QTreeWidgetItem( parent ) {
    setFlags( Qt::ItemIsSelectable | Qt::ItemIsDropEnabled | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled );
    setText( 0, name );

    QIcon icon;
    icon.addFile( QStringLiteral( ":/resources/images/folder.svg" ), QSize(), QIcon::Normal, QIcon::On );
    setIcon( 0, icon );
}

FileItem::FileItem( QTreeWidgetItem* parent, const QString& name ) : QTreeWidgetItem( parent ) {
    setFlags( Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled );
    setText( 0, name );

    QIcon icon;
    icon.addFile( QStringLiteral( ":/resources/images/file.svg" ), QSize(), QIcon::Normal, QIcon::On );
    setIcon( 0, icon );
}

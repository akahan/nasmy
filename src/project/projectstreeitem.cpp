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
#include <QFileInfo>
#include <QDir>

FileItem::FileItem( ProjectBaseItem* parent, const QFileInfo& file_info ) : ProjectBaseItem( parent ) {
    m_absolute_path = file_info.absoluteFilePath();
    m_name = file_info.fileName();
}

FileItem::FileItem( FileItem* parent ) : ProjectBaseItem( parent ) {
    m_absolute_path = parent->m_absolute_path;
    m_name = parent->m_name;
}


ProjectItem::ProjectItem( QTreeWidget* parent, Project* project ) : ProjectBaseItem( parent, project ) {
    setText( 0, project->name() );
    initUI();
}

void ProjectItem::initUI() {
    setFlags( Qt::ItemIsSelectable | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled );

    QIcon icon;
    icon.addFile( QStringLiteral( ":/resources/images/target.svg" ), QSize(), QIcon::Normal, QIcon::On );
    setIcon( 0, icon );

    setSizeHint(0, QSize(0, 20));
}


FolderItem::FolderItem( ProjectBaseItem* parent, const QFileInfo& file_info ) : FileItem( parent, file_info ) {
    setText( 0, file_info.fileName() );
    initUI();
}

void FolderItem::initUI() {
    setFlags( Qt::ItemIsSelectable | Qt::ItemIsDropEnabled | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled );

    QIcon icon;
    icon.addFile( QStringLiteral( ":/resources/images/folder.svg" ), QSize(), QIcon::Normal, QIcon::On );
    setIcon( 0, icon );
}


SourceItem::SourceItem( ProjectBaseItem* parent, const QFileInfo& file_info ) : FileItem( parent, file_info ) {
    setText( 0, file_info.fileName() );
    initUI();
}

// SourceItem::SourceItem(ProjectBaseItem* parent, const QString& rel_path) : FileItem( parent ) {
//     setText( 0, rel_path );
// }

void SourceItem::initUI() {
    setFlags( Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled );

    QIcon icon;
    icon.addFile( QStringLiteral( ":/resources/images/file.svg" ), QSize(), QIcon::Normal, QIcon::On );
    setIcon( 0, icon );
}


TargetItem::TargetItem( ProjectItem* parent, const ProjectTarget& target ) : ProjectBaseItem( parent ) {
    setText( 0, target.name );

    setCheckState(1, Qt::Checked);

    initUI();

    QFont font_target( font( 0 ) );
    font_target.setBold( true );
    if (target.is_main)
        font_target.setUnderline( true );
    //     font_target.setItalic(true);
    //     font_target.setWeight(75);
    setFont( 0, font_target );

}

void TargetItem::initUI() {
    setFlags( Qt::ItemIsSelectable | Qt::ItemIsDropEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled );

    QIcon icon;
    icon.addFile( QStringLiteral( ":/resources/images/target.svg" ), QSize(), QIcon::Normal, QIcon::On );
    setIcon( 0, icon );
}

TargetSourceItem::TargetSourceItem( TargetItem* target, const QFileInfo& file_info  ) : SourceItem( target, file_info ) {
//     setText( 0, project()->projectFolder().relativeFilePath(source->absolutePath()) );
    QString rel_path = project()->projectFolder().relativeFilePath(file_info.absoluteFilePath());
    setText( 0, rel_path );
    initUI();
}

void TargetSourceItem::initUI() {
    setFlags( Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled );

    QIcon icon;
    icon.addFile( QStringLiteral( ":/resources/images/file.svg" ), QSize(), QIcon::Normal, QIcon::On );
    setIcon( 0, icon );
}

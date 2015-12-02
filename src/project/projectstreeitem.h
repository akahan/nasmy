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

#ifndef PROJECTSTREEITEM_H
#define PROJECTSTREEITEM_H

#include <QTreeWidgetItem>

class Project;

class ProjectItem : public QTreeWidgetItem {
    public:
        explicit ProjectItem( QTreeWidget* parent, Project* project );
        inline Project* project() const { return m_project; };

    private:
        Project* m_project;
};

class TargetItem : public QTreeWidgetItem {
    public:
        explicit TargetItem( QTreeWidgetItem* parent, const QString& name );
};

class FolderItem : public QTreeWidgetItem {
    public:
        explicit FolderItem( QTreeWidgetItem* parent, const QString& name );
};

class FileItem : public QTreeWidgetItem {
    public:
        explicit FileItem( QTreeWidgetItem* parent, const QString& name );
};

#endif // PROJECTSTREEITEM_H

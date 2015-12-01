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

#ifndef PROJECTSTREE_H
#define PROJECTSTREE_H

#include <QTreeWidget>

class QTreeWidgetItem;

class ProjectsTree : public QTreeWidget {
    Q_OBJECT

    public:
        explicit ProjectsTree( QWidget* parent );
        ~ProjectsTree() {};

        QTreeWidgetItem* addProjectItem(const QString& name);
        QTreeWidgetItem* addTargetItem(const QString& name, QTreeWidgetItem* project);
        QTreeWidgetItem* addFolderItem(const QString& name, QTreeWidgetItem* parent);
        QTreeWidgetItem* addTargetSourceItem(const QString& name, QTreeWidgetItem* target);
        QTreeWidgetItem* addFileItem(const QString& name, QTreeWidgetItem* folder);

    private:
};

#endif // PROJECTSTREE_H
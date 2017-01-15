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

#ifndef PROJECTSTREE_H
#define PROJECTSTREE_H

#include <QTreeWidget>

class Project;
class QFileInfo;
class ProjectBaseItem;
class ProjectItem;
class FolderItem;
class FileItem;
class SourceItem;
class TargetItem;
class TargetSourceItem;

struct ProjectTarget;

class ProjectsTree : public QTreeWidget {
    Q_OBJECT

    public:
        explicit ProjectsTree( QWidget* parent );
        ~ProjectsTree() {};

        ProjectItem* addProjectItem(Project*);
        FolderItem* addFolderItem( ProjectBaseItem* parent, const QFileInfo& );
        SourceItem* addSourceItem( ProjectBaseItem* folder, const QFileInfo& );
        TargetItem* addTargetItem( ProjectItem*, const ProjectTarget& );
        TargetSourceItem* addTargetSourceItem( TargetItem*, const QFileInfo& );

    private:
};

#endif // PROJECTSTREE_H

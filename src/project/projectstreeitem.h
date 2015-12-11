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
class QFileInfo;

class ProjectBaseItem : public QTreeWidgetItem {
    public:
        ProjectBaseItem( QTreeWidget* tree, Project* project ) : QTreeWidgetItem(tree), m_project( project ) {};
        ProjectBaseItem( QTreeWidgetItem* parent, Project* project ) : QTreeWidgetItem(parent), m_project( project ) {};
        ProjectBaseItem( ProjectBaseItem* parent ) : QTreeWidgetItem(parent), m_project( parent->m_project ) {};

        inline Project* project() const { return m_project; };

        virtual void initUI() = 0;

    private:
        Project* m_project;
};

class FileItem : public ProjectBaseItem {
    public:
        explicit FileItem( ProjectBaseItem* parent, const QFileInfo& );
        explicit FileItem( FileItem* parent );

        inline const QString& absolutePath() const { return m_absolute_path; }
        inline const QString& name() const { return m_name; }

        virtual void initUI() {};

    private:
        QString m_absolute_path;
        QString m_name;
};

class ProjectItem : public ProjectBaseItem {
    public:
        explicit ProjectItem( QTreeWidget* parent, Project* project );

        virtual void initUI();
};

class FolderItem : public FileItem {
    public:
        explicit FolderItem( ProjectBaseItem* parent, const QFileInfo& );

        virtual void initUI();
};

class SourceItem : public FileItem {
    public:
        explicit SourceItem( ProjectBaseItem* parent, const QFileInfo& );
//         explicit SourceItem( ProjectBaseItem* parent, const QString& rel_path );

        virtual void initUI();
};

class TargetItem : public ProjectBaseItem {
    public:
        explicit TargetItem( ProjectItem* parent, const QString& name );

        virtual void initUI();
};

class TargetSourceItem : public SourceItem {
    public:
        explicit TargetSourceItem( TargetItem* parent, const QFileInfo& );

        virtual void initUI();
};

#endif // PROJECTSTREEITEM_H

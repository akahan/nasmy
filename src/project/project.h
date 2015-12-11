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

#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include <QDir>

struct ProjectTarget {
    QString name;
    QStringList files;
};

typedef QList<ProjectTarget> ProjectTargetsList;

class Project : public QObject {
    Q_OBJECT

    friend class ProjectsController;

    public:
        explicit Project( QObject* parent, QString absolute_path );
        ~Project();

        inline const QString& name() const { return m_name; }
        inline const QString& absolutePath() const { return m_absolute_path; }
        inline const QDir& projectFolder() const { return m_project_folder; }
        inline const QString& assemblyOptions() const { return assembly_options; }
        inline const QString& linkingOptions() const { return linking_options; }
        inline const bool verboseBuild() const { return verbose_build; }
        inline const ProjectTargetsList& targets() const { return m_targets; }
        inline const QStringList& files() const { return m_files; }

        void open();

    private:
        QString m_name;
        QString m_absolute_path;
        QDir m_project_folder;
        int arch_id;
        QString assembly_options;
        QString linking_options;
        bool verbose_build;
        ProjectTargetsList m_targets;
        QStringList m_files;
};

#endif // PROJECT_H

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

#ifndef FILE_H
#define FILE_H

#include <QObject>

class AsmEdit;
class Project;
class Highlighter;
class Assembler;
// class QStandardItem;
// class QStandardItemModel;
// class QCompleter;
// class QStringListModel;

class File : public QObject {
    Q_OBJECT

    friend class FilesController;

    public:
        explicit File( QObject* parent, QString absolute_path = "" );
        ~File();

        inline const QString& title() const { return m_title; }
        inline const QString& absolutePath() const { return m_absolute_path; }
        void setAbsolutePath( const QString& value );

        inline Project* project() const { return m_project; }
        inline AsmEdit* editor() const { return m_editor; }

        void open();
        void save();

        void setConnectionsToEditor();

    signals:

    public slots:

    private:
        QString m_title;
        QString m_absolute_path;

        Project* m_project;
        AsmEdit* m_editor;
        Highlighter* m_highlighter;
        Assembler* m_asm;
};

#endif // FILE_H

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

#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include <QObject>

class MainWindow;
class QString;
class Highlighter;
class QStandardItem;
class QStandardItemModel;
class QCompleter;
class QStringListModel;
class AsmEdit;

class FileController : public QObject {
    Q_OBJECT

    public:
        explicit FileController( MainWindow* parent, QString absolute_path = "" );
        ~FileController();

        inline const QString& title() const { return title_str; }
        inline const QString& absolutePath() const { return absolute_path; }
        void setAbsolutePath( const QString& value );

        inline AsmEdit* editor() const { return asm_edit; }

        void open();
        void save();

        void setConnectionsToEditor();

    signals:

    public slots:

    private:
        QString title_str;
        QString absolute_path;

        AsmEdit* asm_edit;
};

#endif // FILECONTROLLER_H

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

#include "file.h"
#include "nasmy.h"
#include "asmedit.h"
// #include "completerpopupmodel.h"

#include <QFileInfo>
// #include <QStandardItemModel>
// #include <QApplication>
// #include <QRegExp>
// #include <QStringListModel>
// #include <QUrl>
#include <QDir>
#include <QtDebug>

File::File( QObject* parent, QString absolute_path ) : QObject( parent ) {
    m_editor = new AsmEdit( Nasmy::mainwindow() );

    setAbsolutePath(absolute_path);
}

File::~File() {
    delete m_editor;
}

void File::setAbsolutePath(const QString& value) {
    absolute_path = value;
    if ( !absolute_path.isEmpty() ) {
        title_str = QFileInfo( absolute_path ).fileName();

        if ( title_str.length() > 20 ) {
            title_str = title_str.left( 12 ) + "...";
        }
    }
    else {
        title_str = tr( "Untitled" );
    }
}

void File::open() {
    QFile file( absolute_path );
    if ( !file.open( QFile::ReadOnly | QFile::Text ) ) {
        throw file.errorString();
    }

    QString text = file.readAll();

    if ( !text.isEmpty() ) {
        m_editor->setPlainText( text );
    }
}

void File::save() {
    QFile file( absolute_path );

    if ( !file.open( QFile::WriteOnly | QFile::Text ) ) {
        throw file.errorString();
    }

    QTextStream out( &file );
    out << m_editor->toPlainText();

    m_editor->document()->setModified( false );
}

void File::setConnectionsToEditor() {
//     asm_edit->disconnect();
}


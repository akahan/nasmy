/*
 * <one line to give the library's name and an idea of what it does.>
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

#include "projectwindow.h"
#include <QPushButton>
#include <QDir>
#include <QStandardPaths>
#include <QFileDialog>
#include <QSettings>

#include <QtDebug>

ProjectWindow::ProjectWindow( QWidget* parent, bool is_new ) : QDialog( parent ) {
    setupUi( this );

    setAttribute(Qt::WA_DeleteOnClose);
    buttonBox->button( QDialogButtonBox::Ok )->setEnabled( false );

    if ( is_new ) {
        setWindowTitle( tr( "New project" ) );
        buttonBox->button( QDialogButtonBox::Apply )->setVisible( false );
        pathEdit->setText( QStandardPaths::writableLocation( QStandardPaths::HomeLocation ) );
    }
    else {
        setWindowTitle( tr( "Edit project" ) );
        readProject();
    }
}

ProjectWindow::~ProjectWindow() {
    qDebug() << "~ProjectWindow";
}

QString const ProjectWindow::exec_and_return_path() {
    if ( exec() ) {
        QString project_absolute_path = QString( "%1/%2.nasmy" ).arg( pathEdit->text() ).arg( nameEdit->text() );
        return project_absolute_path;
    }
    return QString();
}

void ProjectWindow::readProject() {
//     QSettings settings();
}

void ProjectWindow::saveProject() {
    QDir dir;

    QString project_folder = QString( "%1/%2" ).arg( pathEdit->text() ).arg( nameEdit->text() );
    if ( dir.mkpath( project_folder ) ) {
        QString project_absolute_path = QString( "%1/%2.nasmy" ).arg( project_folder ).arg( nameEdit->text() );
        QSettings settings( project_absolute_path, QSettings::NativeFormat );
        settings.beginGroup( "project" );
        settings.setValue( "name", nameEdit->text() );
        settings.setValue( "arch_id", archiComboBox->currentIndex() );
        settings.setValue( "assembly_options", assemblyOptionsEdit->text() );
        settings.setValue( "linking_options", linkingOptionsEdit->text() );
        settings.setValue( "verbose_build", verboseBuild->isChecked() );
        settings.endGroup();
        settings.beginWriteArray( "targets" );
        settings.setArrayIndex( 0 );
        settings.setValue( "name", nameEdit->text() );
        QStringList files;
        files << "src/main.asm";
        settings.setValue( "files", files );
        settings.endArray();
    }
}

void ProjectWindow::on_buttonBox_accepted() {
    saveProject();
    accept();
}

void ProjectWindow::on_buttonBox_rejected() {
    reject();
}

void ProjectWindow::on_nameEdit_textChanged(const QString&) {
    bool can_finish = nameEdit->text().length() > 2 && !pathEdit->text().isEmpty();
    buttonBox->button( QDialogButtonBox::Ok )->setEnabled( can_finish );
    buttonBox->button( QDialogButtonBox::Apply )->setEnabled( can_finish );
}

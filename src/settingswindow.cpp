/*
 * <one line to give the library's name and an idea of what it does.>
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

#include "settingswindow.h"
#include <QSettings>

SettingsWindow::SettingsWindow( QWidget* parent ) : QDialog( parent ) {
    setupUi( this );
    readSettings();
}

SettingsWindow::~SettingsWindow() {
}

void SettingsWindow::readSettings() {
    QSettings settings;
}

void SettingsWindow::saveSettings() {
}

void SettingsWindow::restoreDefaults() {
}

void SettingsWindow::on_buttonBox_accepted() {
    saveSettings();
    accept();
}

void SettingsWindow::on_buttonBox_rejected() {
    reject();
}

void SettingsWindow::on_buttonBox_clicked( QAbstractButton* button ) {
    switch(buttonBox->standardButton(button)) {
        case QDialogButtonBox::Apply: {
            saveSettings();
            break;
        }

        case QDialogButtonBox::RestoreDefaults: {
            restoreDefaults();
            break;
        }

        default: break;
    }
}

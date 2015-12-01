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

#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>

#include "ui_settingswindow.h"

class SettingsWindow : public QDialog, private Ui::SettingsWindow {
    Q_OBJECT
    public:
        explicit SettingsWindow( QWidget* parent );
        ~SettingsWindow();

    private:
        void readSettings();
        void saveSettings();
        void restoreDefaults();

    private slots:
        void on_buttonBox_accepted();
        void on_buttonBox_rejected();
        void on_buttonBox_clicked(QAbstractButton*);
};

#endif // SETTINGSWINDOW_H

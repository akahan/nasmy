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

#include "mainwindow.h"
#include <QTranslator>
#include <QApplication>

int main( int argc, char *argv[] ) {
    QApplication app( argc, argv );

    app.setApplicationDisplayName( QObject::tr( "Nasmy" ) );
    app.setOrganizationName( "nasmy" );

    QTranslator qtTranslator;
    qtTranslator.load( ":/translations/nasmy_" + QLocale::system().name() );
    app.installTranslator( &qtTranslator );

//     MainWindow& w = MainWindowInstance;
//     w.show();
    MainWindow w;
    w.show();

    return app.exec();
}

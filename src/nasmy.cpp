
#include "nasmy.h"

namespace Nasmy {
    MainWindow* nasmy_ui = NULL;

    MainWindow* mainwindow() {
        return Nasmy::nasmy_ui;
    }

    ProjectsController* pc() {
        static ProjectsController instance;
        return &instance;
    }

    FilesController* fc() {
        static FilesController instance;
        return &instance;
    }

    // **********************************************************************
    // **********************************************************************
    // **********************************************************************

    MsgButton question( const QString& text, MsgButtons buttons, MsgButton defaultButton ) {
        return QMessageBox::question( nasmy_ui, AppName, text, buttons, defaultButton );
    }

    MsgButton warning( const QString& text, MsgButtons buttons, MsgButton defaultButton ) {
        return QMessageBox::warning( nasmy_ui, AppName, text, buttons, defaultButton );
    }

    MsgButton critical( const QString& text, MsgButtons buttons, MsgButton defaultButton ) {
        QString a = AppName;
        return QMessageBox::critical( nasmy_ui, AppName, text, buttons, defaultButton );
    }

    MsgButton information( const QString& text, MsgButtons buttons, MsgButton defaultButton ) {
        return QMessageBox::information( nasmy_ui, AppName, text, buttons, defaultButton );
    }
}

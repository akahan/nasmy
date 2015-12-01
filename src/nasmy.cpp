
#include "nasmy.h"

namespace Nasmy {
    QWidget* nasmy_ui = NULL;

    MainWindow* mainwindow() {
        return qobject_cast<MainWindow*>(Nasmy::nasmy_ui);
    }
}

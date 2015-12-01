
#include <QApplication>
#include "editor/asmedit.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AsmEdit * w = new AsmEdit();
//     w->move(1600,600);
    w->show();
    return a.exec();
}

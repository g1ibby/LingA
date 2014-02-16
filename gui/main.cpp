#include "lingagui.h"
#include "main.h"
#include <QApplication>

int lib_main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LingAgui w;
    w.show();

    return a.exec();
}

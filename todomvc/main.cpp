#include "todomvc.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    todomvc w;
    w.resize(650,650);
    w.show();
    return a.exec();
}

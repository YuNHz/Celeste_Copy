#include "game.h"
#include <QApplication>
#include <QFile>
#include "widget.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Widget Celeste;
    Celeste.show();
    return a.exec();
}

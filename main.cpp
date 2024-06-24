#include <QtWidgets/QApplication>
#include <QLocale>
#include <QTranslator>
#include "Window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Window game;
    game.show();

    return a.exec();
}

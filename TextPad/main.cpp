#include <QApplication>
#include <QtWidgets>
#include "textedit.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TextEdit txt;
    txt.setGeometry(500, 300, 500, 300); //размер и положение виджета
    txt.show();
    return app.exec();
}

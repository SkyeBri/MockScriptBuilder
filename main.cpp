#include "ScriptBuilderMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScriptBuilderMainWindow w(a);
    w.show();

    return a.exec();
}

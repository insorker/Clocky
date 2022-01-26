#include "search.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Search w;
    w.show();
    return a.exec();
}

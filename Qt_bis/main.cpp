#include "bis.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bis w;
    w.show();
    return a.exec();
}

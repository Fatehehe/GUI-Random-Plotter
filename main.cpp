#include "fukuroplotter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FukuroPlotter w;
    w.show();
    return a.exec();
}

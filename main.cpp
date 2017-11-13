#include "view.h"
#include <QApplication>
#include "Magick++.h"
#include <QDebug>
using namespace Magick;


int main(int argc, char *argv[])
{
    InitializeMagick(argv[0]);
    QApplication a(argc, argv);

    qDebug() << argv[0];
    Model m;
    View v(&m);
    v.show();

    return a.exec();
}

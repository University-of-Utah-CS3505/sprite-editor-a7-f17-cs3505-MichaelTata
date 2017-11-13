#include "view.h"
#include <QApplication>
#include <Magick++.h>
#include <QDebug>
using namespace Magick;


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    //InitializeMagick(*argv);
    //Magick::Image img1("100x100", "white");
    qDebug() << argv[0];
    Model m;
    View v(&m);
    v.show();

    return a.exec();
}

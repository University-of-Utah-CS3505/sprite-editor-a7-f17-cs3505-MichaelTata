#include "view.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    qDebug() << argv[0];

    Model m;
    View v(&m);
    v.show();

    return a.exec();
}

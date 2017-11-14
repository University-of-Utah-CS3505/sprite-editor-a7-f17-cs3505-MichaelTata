#include "view.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Model m;
    View v(&m);
    v.show();
    return a.exec();
}

#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include "model.h"
#include "drawingwidget.h"
#include <QObject>

namespace Ui {
class View;
}

class View : public QMainWindow
{
    Q_OBJECT

public:
    explicit View(Model* m, QWidget *parent = 0);
    ~View();

private:
    Ui::View *ui;

public slots:




signals:


};

#endif // VIEW_H

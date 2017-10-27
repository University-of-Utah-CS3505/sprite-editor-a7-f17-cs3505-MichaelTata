#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include "model.h"

namespace Ui {
class View;
}

class View : public QMainWindow
{
    Q_OBJECT

public:
    explicit View(Model*, QWidget *parent = 0);
    ~View();

private:
    Ui::View *ui;
};

#endif // VIEW_H

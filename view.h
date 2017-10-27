#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>

namespace Ui {
class View;
}

class View : public QMainWindow
{
    Q_OBJECT

public:
    explicit View(QWidget *parent = 0);
    ~View();

private:
    Ui::View *ui;
};

#endif // VIEW_H

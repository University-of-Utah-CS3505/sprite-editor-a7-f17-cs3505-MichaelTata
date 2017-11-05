#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include "model.h"
#include "drawingwidget.h"
#include <QObject>
#include <QTimer>

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

    //Timer for how fast to send frames to be displayed.
    QTimer *frameTimer;

public slots:
    void fpsChange(int);




signals:


};

#endif // VIEW_H

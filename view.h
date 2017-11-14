#ifndef VIEW_H
#define VIEW_H

#include "createnewsprite.h"
#include <QMainWindow>
#include "model.h"
#include "drawingwidget.h"
#include <QObject>
#include <QTimer>
#include <QScrollArea>

namespace Ui {
class View;
}

class View : public QMainWindow {
    Q_OBJECT

public:
    explicit View(Model* m, QWidget *parent = 0);
    ~View();

private:
    Ui::View *ui;

    // Timer for how fast to send frames to be displayed.
    QTimer *frameTimer;

    // Creates a new sprite dialog.
    CreateNewSprite *newSprite;

public slots:
    // This slot deals with changing the fps for the frame previews.
    void fpsChange(int);

    // This slot deals with opening a new sprite window to choose pixel size.
    void openNewSpriteWindow();

    // This slot changes the theme of the editor to a dark theme.
    void themeDark();

    // This slot changes the theme of the editor to a light theme.
    void themeLight();

signals:
};

#endif // VIEW_H

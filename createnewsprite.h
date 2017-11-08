#ifndef NEWSPRITEWINDOW_H
#define NEWSPRITEWINDOW_H

#include <QDialog>

namespace Ui {
class NewSpriteWindow;
}

class CreateNewSprite : public QDialog
{
    Q_OBJECT

public:
    explicit CreateNewSprite(QWidget *parent = 0);
    ~CreateNewSprite();

signals:
    void sendSpriteInfo(int, int);

public slots:
    void getInfoToSend();


private:
    Ui::NewSpriteWindow *ui;
};

#endif // NEWSPRITEWINDOW_H

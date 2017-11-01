#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H


#include <QPainter>
#include <QImage>



#include <QWidget>

class DrawingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingWidget(QWidget *parent = 0);

private:
    QImage currImage;
    QSize scale;
    int scaleFactor;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void resizeEvent(QResizeEvent *e);

signals:
    //Signal for funneling mouse click
    void click(QMouseEvent *e);

    //Signal for funneling mouse move
    void mouseMove(QMouseEvent *e);

    //Signal for funneling unclick(Using this so we can create a "preview" of
    //where we are moving a line or rect if we are using them
    void unclick(QMouseEvent *e);

    //used to control the rescale factor for our image, so we can resize and still maintain the original image
    void rescale(QSize);


public slots:
    //Slot for resizing board?? Will probably need it to resize widget to fit an image.
    void changeScale(int);

    void drawUpdatedImage(QImage ourIm);

};

#endif // DRAWINGWIDGET_H

#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QMouseEvent>
#include <math.h>
#include <QPainter>
#include <QImage>
#include <QWidget>
#include <QPoint>
#include <QColor>

class DrawingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingWidget(QWidget *parent = 0);

private:
    //This is used to paint to the drawingboard
    //Temp is used for preview functionality
    QImage currImage;
    QImage tempImage;

    //This is used to control the "scale" or zoom and unzoom
    qreal scaleFactor;

    //Used to determine if a definitive scale is set.
    bool defScale;

    //Controls where the image is drawn from, which allows us to
    //Scroll while zoomed or unzoomed.
    int horizontalScroll;
    int verticalScroll;

protected:
    //All of these are used to manipulate the drawing board and
    //To view the drawingboard(paint)
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void resizeEvent(QResizeEvent *e);

signals:
    //Signal for funneling mouse click to the model to draw
    void click(QMouseEvent *e, int, int);

    //Signal for funneling mouse move to the model for previewing a draw and highlighting
    void mouseMove(QMouseEvent *e, int, int);

    //Signal for funneling unclick(Using this so we can create a "preview" of
    //where we are moving a line or rect if we are using them
    void unclick(QMouseEvent *e, int, int);

    //used to control the rescale factor zooming in our image, so we can resize and still maintain the original image
    void sendScaleIn(QSize);

    //used to control the rescale factor zooming out our image, so we can resize and still maintain the original image
    void sendScaleOut(QSize);

public slots:
    //Creates a new board(needed for when we new or load new sprites)
    void createNewBoard(int, int);

    //Highlights a pixel designated by the model
    void highlightPixel(QPoint coords);

    //Used to scale in or zoom on the image
    void scaleIn(double);

    //Used to scroll horizontal, controls the left to right zoom/scroll movements.
    void scrollHor(int);

    //Used to scroll vertically, controls up and down zoom/scroll movements.
    void scrollVer(int);

    //Scales out of the image while zoomed.
    void scaleOut(double);

    //Used with previewws in mind, to set a definitive scale that will not change.
    void setDefinitiveScale(int, int);

    //Used to take the image from the model and draw it.
    void drawUpdatedImage(QImage ourIm);
};

#endif // DRAWINGWIDGET_H

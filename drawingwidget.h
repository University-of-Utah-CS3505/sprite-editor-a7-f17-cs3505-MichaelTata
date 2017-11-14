#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

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
    QImage currImage;
    QImage tempImage;
    qreal scaleFactor;
    bool defScale;
    int horizontalScroll;
    int verticalScroll;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void resizeEvent(QResizeEvent *e);

signals:
    //Signal for funneling mouse click
    void click(QMouseEvent *e, int, int);

    //Signal for funneling mouse move
    void mouseMove(QMouseEvent *e, int, int);

    //Signal for funneling unclick(Using this so we can create a "preview" of
    //where we are moving a line or rect if we are using them
    void unclick(QMouseEvent *e, int, int);

    //used to control the rescale factor zooming in our image, so we can resize and still maintain the original image
    void sendScaleIn(QSize);

    //used to control the rescale factor zooming out our image, so we can resize and still maintain the original image
    void sendScaleOut(QSize);

public slots:
    void createNewBoard(int, int);

    void highlightPixel(QPoint coords);

    void scaleIn(double);

    void scrollHor(int);

    void scrollVer(int);

    void scaleOut(double);

    //Testing this out for fixing the preview bug.
    void setDefinitiveScale(int, int);

    void drawUpdatedImage(QImage ourIm);
};

#endif // DRAWINGWIDGET_H

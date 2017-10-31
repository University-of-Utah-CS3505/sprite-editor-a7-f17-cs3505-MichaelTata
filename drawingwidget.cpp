#include "drawingwidget.h"
#include <iostream>
#include <QMouseEvent>
#include <math.h>

DrawingWidget::DrawingWidget(QWidget *parent) : QWidget(parent), scale(500, 500),
    currImage(500, 500, QImage::Format_ARGB32)
{
    //Default Gray drawing board, Can set variable size here.
    //currImage = QPixmap(500, 500).toImage();

    currImage.fill(Qt::gray);


}

void DrawingWidget::drawImage(QImage ourIm)
{
    currImage = ourIm.scaled(scale, Qt::KeepAspectRatio);
    repaint();
}

void DrawingWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawImage(0, 0, currImage, 0, 0, currImage.width(), currImage.height() );
}

void DrawingWidget::mousePressEvent(QMouseEvent *e)
{
    emit click(e);
}

void DrawingWidget::mouseReleaseEvent(QMouseEvent *e)
{

}

void DrawingWidget::resizeEvent(QResizeEvent *e)
{
    //Get new width and height of the drawing widget for scale and set new image.
    //Round to nearest 100th for res
    int h = round((double)this->height()/100 + 0.5)*100;
    int w = round((double)this->width()/100 + 0.5)*100;

    scale.setWidth(w);
    scale.setHeight(h);
    std::cout << w << "-wid, height - " << h << " ";

    currImage = currImage.scaled(scale, Qt::KeepAspectRatio);

    emit rescale(scale);

}

void DrawingWidget::mouseMoveEvent(QMouseEvent *e)
{

    emit mouseMove(e);


}


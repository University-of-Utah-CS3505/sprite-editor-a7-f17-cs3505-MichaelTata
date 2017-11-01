#include "drawingwidget.h"
#include <iostream>
#include <QMouseEvent>
#include <math.h>

DrawingWidget::DrawingWidget(QWidget *parent) : QWidget(parent),
    currImage(500, 500, QImage::Format_ARGB32)
{

    scaleFactor = 1;
    //Default Gray drawing board, Can set variable size here.
    //currImage = QPixmap(500, 500).toImage();

    currImage.fill(Qt::gray);


}

void DrawingWidget::drawUpdatedImage(QImage ourIm)
{
    ourIm.setDevicePixelRatio(scaleFactor);
    currImage = ourIm;
    update();
}

void DrawingWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawImage(0, 0, currImage, 0, 0, currImage.width()/scaleFactor, currImage.height()/scaleFactor );




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



    //scale.setWidth(w);
    //scale.setHeight(h);
    //std::cout << w << "-wid, height - " << h << " ";

    //currImage = currImage.scaled(scale, Qt::KeepAspectRatio);

    //emit rescale(scale);

}

void DrawingWidget::scaleIn(int passScaleFactor)
{


    //scale.setWidth(scale.width() * passScaleFactor);
    //scale.setHeight(scale.height()* passScaleFactor);

    scaleFactor /= passScaleFactor;

    currImage.setDevicePixelRatio(scaleFactor);
    update();
}

void DrawingWidget::scaleOut(int passScaleFactor)
{
    scaleFactor *= passScaleFactor;

    currImage.setDevicePixelRatio(scaleFactor);
    update();
}




void DrawingWidget::mouseMoveEvent(QMouseEvent *e)
{

    emit mouseMove(e);


}


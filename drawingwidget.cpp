#include "drawingwidget.h"
#include <iostream>
#include <QMouseEvent>

DrawingWidget::DrawingWidget(QWidget *parent) : QWidget(parent)
{
    //Default Gray drawing board, Can set variable size here.
    currImage = QPixmap(400, 480).toImage();

    currImage.fill(Qt::gray);

}


void DrawingWidget::drawImage(QImage ourIm)
{

    currImage = ourIm;

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

void DrawingWidget::mouseMoveEvent(QMouseEvent *e)
{

    emit mouseMove(e);

}


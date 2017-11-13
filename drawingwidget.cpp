#include "drawingwidget.h"
#include <iostream>
#include <QMouseEvent>
#include <math.h>

#include <QDebug>


DrawingWidget::DrawingWidget(QWidget *parent) : QWidget(parent),
    currImage(100, 100, QImage::Format_ARGB32) {

    horizontalScroll = 0;
    verticalScroll = 0;


    scaleFactor = 1;
    //Default Gray drawing board, Can set variable size here.
    //currImage = QPixmap(500, 500).toImage();

    currImage.fill(Qt::transparent);
    tempImage = currImage;


}

void DrawingWidget::scrollHor(int change) {
    horizontalScroll = change;
    update();
}

void DrawingWidget::scrollVer(int change) {
    verticalScroll = change;
    update();
}

void DrawingWidget::createNewBoard(int w, int h) {
    scaleFactor = 1;
    currImage.fill(Qt::transparent);

    //QImage temp(w, h, QImage::Format_ARGB32);

    currImage= QImage(w, h,  QImage::Format_ARGB32 );
    tempImage = currImage;

}


void DrawingWidget::drawUpdatedImage(QImage ourIm) {
    ourIm.setDevicePixelRatio(scaleFactor);
    currImage = ourIm;
    tempImage = currImage;
    update();
}

void DrawingWidget::paintEvent(QPaintEvent *e) {
    //Changes here to make scrolling work? depending on where we are in image
    //By that i mean change tempimage.width for sw, and height for sh, which should change
    //what portion of draw we are at.
    //if defscale and draw scaled image..



    QPainter painter(this);

    //if(defScale)

        //qDebug() << tempImage.size().width() << "-" << tempImage.size().height();
    painter.drawImage(0, 0, tempImage, horizontalScroll, verticalScroll, 0, 0);
    //else
       // painter.drawImage(0, 0, tempImage.scaled(200, 200, Qt::IgnoreAspectRatio), 0, 0);

}

void DrawingWidget::mousePressEvent(QMouseEvent *e) {
    emit click(e, horizontalScroll, verticalScroll);
}

void DrawingWidget::mouseReleaseEvent(QMouseEvent *e) {
    emit unclick(e, horizontalScroll, verticalScroll);
}

void DrawingWidget::resizeEvent(QResizeEvent *e) {



    //scale.setWidth(w);
    //scale.setHeight(h);
    //std::cout << w << "-wid, height - " << h << " ";

    //currImage = currImage.scaled(scale, Qt::KeepAspectRatio);

    //emit rescale(scale);

}



void DrawingWidget::setDefinitiveScale(int w, int h) {

}


void DrawingWidget::scaleIn(int passScaleFactor) {


    scaleFactor /= passScaleFactor;

    currImage.setDevicePixelRatio(scaleFactor);
    tempImage.setDevicePixelRatio(scaleFactor);
    update();
}

void DrawingWidget::scaleOut(int passScaleFactor) {
    scaleFactor *= passScaleFactor;

    currImage.setDevicePixelRatio(scaleFactor);
    tempImage.setDevicePixelRatio(scaleFactor);
    update();
}

void DrawingWidget::mouseMoveEvent(QMouseEvent *e) {
    emit mouseMove(e, horizontalScroll, verticalScroll);
}

void DrawingWidget::highlightPixel(QPoint point) {
    tempImage = currImage;
    QColor currColor = tempImage.pixelColor(point);
    currColor.setAlpha(100);
    tempImage.setPixelColor(point, currColor);
    update();
}



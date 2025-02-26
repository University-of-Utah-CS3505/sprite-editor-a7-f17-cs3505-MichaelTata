#include "drawingwidget.h"


DrawingWidget::DrawingWidget(QWidget *parent) : QWidget(parent),
    currImage(100, 100, QImage::Format_ARGB32_Premultiplied) {

    horizontalScroll = 0;
    verticalScroll = 0;
    scaleFactor = 1;

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
    currImage= QImage(w, h,  QImage::Format_ARGB32_Premultiplied );
    tempImage = currImage;
}

void DrawingWidget::drawUpdatedImage(QImage ourIm) {
    ourIm.setDevicePixelRatio(scaleFactor);
    currImage = ourIm;
    tempImage = currImage;
    update();
}

void DrawingWidget::paintEvent(QPaintEvent *e) {

    QPainter painter(this);
    painter.drawImage(0, 0, tempImage, horizontalScroll, verticalScroll, 0, 0);
}

void DrawingWidget::mousePressEvent(QMouseEvent *e) {
    emit click(e, horizontalScroll, verticalScroll);
}

void DrawingWidget::mouseReleaseEvent(QMouseEvent *e) {
    emit unclick(e, horizontalScroll, verticalScroll);
}

void DrawingWidget::resizeEvent(QResizeEvent *e) {
}



void DrawingWidget::setDefinitiveScale(int w, int h) {
}


void DrawingWidget::scaleIn(double passScaleFactor) {
    scaleFactor /= passScaleFactor;

    currImage.setDevicePixelRatio(scaleFactor);
    tempImage.setDevicePixelRatio(scaleFactor);
    update();
}

void DrawingWidget::scaleOut(double passScaleFactor) {
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

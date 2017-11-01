#include "model.h"
#include <iostream>

Model::Model(QObject *parent) : QObject(parent), currentImage(100, 100, QImage::Format_ARGB32)
{
    //Temporary default value as we use 500,500 for default image
    xScale = 1;
    yScale = 1;


    //currentImage(64, 64, QImage::Format_ARGB32);
    //Default value until we add load and creation of custom sized sprite
    //currentImage = QPixmap(64, 64).toImage();
    currentImage.fill(Qt::gray);

    frames.push_back(currentImage);

    currentTool = 0;

    painter.begin(&currentImage);

    painter.setPen(Qt::black);

    emit redrawImage(currentImage);
}

//Slot to receive a drawing event. Used Specifically for when a click(or unclick) has occurred
void Model::manipulateImage(QMouseEvent *e)
{

    int tempX = e->pos().x() / xScale;
    int tempY = e->pos().y() / yScale;
    QPoint point(tempX, tempY);

    //Left mouse button click or click+hold+drag?
    if(e->buttons() == Qt::LeftButton)
    {
        switch(currentTool) {
        case 0:

            //Make sure we only allow ~25 or so undo otherwise program crashes
            //undoes.push_back(currentImage);
            painter.drawPoint(point);
            emit redrawImage(currentImage);
            break;
        }
    }
    else {
        if (tempX < currentImage.width() && tempY < currentImage.height())
            emit sendHighlight(point);
    }
}

void Model::scaleOut()
{
    xScale/=2;
    yScale/=2;

    emit sendScaleOut(2);


}


void Model::scaleIn()
{

    xScale *= 2;
    yScale *= 2;

    emit sendScaleIn(2);


}

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

//Slot for released mouse click event. So if we have a shape/line tool chosen
//This will add the actual shape to the image. This is needed as manipulate image only handles
//Previews, as the mouse event cannot be used to determine mouse button release, only move and click/drag
void Model::addShapeToImage(QMouseEvent *e)
{
    QPointF firstPt(shapeCoordX, shapeCoordY);
    QPointF secondPt(e->pos().x()/xScale, e->pos().y()/yScale);

    switch(currentTool)
    {
        case 4:
            painter.drawLine(firstPt, secondPt);

            emit redrawImage(currentImage);
        break;
    }

    activePreview = false;
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

        case 1:

            break;

        case 4:
            //factor this into its own method to be used by all tools
            if(activePreview)
            {
                QImage tempIm = currentImage;
                QPainter tempPaint(&tempIm);
                QPointF firstPt(shapeCoordX, shapeCoordY);
                QPointF secondPt(e->pos().x()/xScale, e->pos().y()/yScale);
                tempPaint.drawLine(firstPt, secondPt);

                emit redrawImage(tempIm);


            }
            else
            {
                activePreview = true;
                shapeCoordX = e->pos().x() / xScale;
                shapeCoordY = e->pos().y() / yScale;
                //save image here?

            }




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




//All tool selection slots go here.

void Model::penSelected()
{
    currentTool = 0;

}

void Model::lineSelected()
{
    currentTool = 4;

}

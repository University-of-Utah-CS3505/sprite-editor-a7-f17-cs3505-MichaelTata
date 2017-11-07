#include "model.h"
#include <iostream>
#include <QColorDialog>
#include <QColor>
#include <QDebug>
#include <queue>

Model::Model(QObject *parent) : QObject(parent), currentImage(100, 100, QImage::Format_ARGB32)
{
    //Temporary default value as we use 500,500 for default image
    xScale = 1;
    yScale = 1;

    currentFrame = 0;
    currentColor = Qt::black;

    //currentImage(64, 64, QImage::Format_ARGB32);
    //Default value until we add load and creation of custom sized sprite
    //currentImage = QPixmap(64, 64).toImage();
    currentImage.fill(Qt::gray);

    frames.push_back(currentImage);

    currentTool = 0;

    painter.begin(&currentImage);

    painter.setPen(currentColor);


    emit redrawImage(currentImage);
}

//Slot for released mouse click event. So if we have a shape/line tool chosen
//This will add the actual shape to the image. This is needed as manipulate image only handles
//Previews, as the mouse event cannot be used to determine mouse button release, only move and click/drag
void Model::addShapeToImage(QMouseEvent *e)
{
    QPointF firstPt(shapeCoordX, shapeCoordY);
    QPointF secondPt(e->pos().x()/xScale, e->pos().y()/yScale);
    QRectF tempRec = getRectangle(firstPt, secondPt);
    switch(currentTool)
    {
        case 4:
            painter.drawLine(firstPt, secondPt);

            emit redrawImage(currentImage);
        break;

        case 5:

            painter.drawRect(tempRec);

            emit redrawImage(currentImage);
        break;
        case 6:
            painter.drawEllipse(tempRec);

            emit redrawImage(currentImage);
        break;
    }

    activePreview = false;
}


//Slot to receive a drawing event. Used Specifically for when a click(or unclick) has occurred
void Model::manipulateImage(QMouseEvent *e)
{
    //qDebug() << "manipulating";
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

//        case 1:

//            //painter.setPen(Qt::gray);
//            painter.drawPoint(point);
//            emit redrawImage(currentImage);
//            break;

        case 3:
            fill(point);
//            fillZone(point);

//            qDebug() << "fillPixel called : " << fillCount << " times.";
//            qDebug() << "fillPixel entered if statement: " << fillCountTwo << " times.";
//            fillCount = 0;
//            fillCountTwo = 0;
            emit redrawImage(currentImage);
            break;

        case 4:
            //factor this into its own method to be used by all tools
//            if(activePreview)
//            {
//                QImage tempIm = currentImage;
//                QPainter tempPaint(&tempIm);
//                tempPaint.setPen(painter.pen().color());
//                QPointF firstPt(shapeCoordX, shapeCoordY);
//                QPointF secondPt(e->pos().x()/xScale, e->pos().y()/yScale);
//                tempPaint.drawLine(firstPt, secondPt);

//                emit redrawImage(tempIm);



//            }
//            else
//            {
//                activePreview = true;
//                shapeCoordX = e->pos().x() / xScale;
//                shapeCoordY = e->pos().y() / yScale;


//            }
            drawShapePreview(e);
            break;

         case 5:

//            if(activePreview)
//            {
//                //Draw a temporary image to send to be drawn
//                QImage tempIm = currentImage;
//                QPainter tempPaint(&tempIm);
//                tempPaint.setPen(painter.pen().color());
//                QPointF firstPt(shapeCoordX, shapeCoordY);
//                QPointF secondPt(e->pos().x()/xScale, e->pos().y()/yScale);
//                tempPaint.drawRect(getRectangle(firstPt, secondPt));

//                emit redrawImage(tempIm);
//            }
//            else
//            {
//                activePreview = true;
//                shapeCoordX = e->pos().x() / xScale;
//                shapeCoordY = e->pos().y() / yScale;
//            }
            drawShapePreview(e);
            break;

        case 6:

//           if(activePreview)
//           {
//               //Draw a temporary image to send to be drawn
//               QImage tempIm = currentImage;
//               QPainter tempPaint(&tempIm);
//               tempPaint.setPen(painter.pen().color());
//               QPointF firstPt(shapeCoordX, shapeCoordY);
//               QPointF secondPt(e->pos().x()/xScale, e->pos().y()/yScale);
//               tempPaint.drawEllipse(getRectangle(firstPt, secondPt));

//               emit redrawImage(tempIm);
//           }
//           else
//           {
//               activePreview = true;
//               shapeCoordX = e->pos().x() / xScale;
//               shapeCoordY = e->pos().y() / yScale;
//           }

           drawShapePreview(e);
           break;



        }
    }
    else {
        if (tempX < currentImage.width() && tempY < currentImage.height())
            emit sendHighlight(point);
    }
}

QRectF Model::getRectangle(QPointF pivot, QPointF secondPt)
{

    //Second Pt is top left of rect, pivot is bottom right.
    if(secondPt.x() < pivot.x() && secondPt.y() < pivot.y())
    {
        QRectF temp(secondPt, pivot);
        return temp;
    }
    //Second pt is top right of rect, pivot is bottom left.
    else if(secondPt.x() > pivot.x() && secondPt.y() < pivot.y())
    {
        QRectF temp;
        temp.setTopRight(secondPt);
        temp.setBottomLeft(pivot);
        //do we need to add top left and bottom right for this to work?
        return temp;
    }
    //Second pt is bottom left of rect, pivot is top right.
    else if(secondPt.x() < pivot.x() && secondPt.y() > pivot.y())
    {
        QRectF temp;
        temp.setBottomLeft(secondPt);
        temp.setTopRight(pivot);
        return temp;
    }
//    //Second pt is bottom right, pivot is top left.
//    else if(secondPt.x() > pivot.x() && secondPt.y() > pivot.y())
//    {
//        QRectF temp(pivot, secondPt);
//        return temp;
//    }
    //Second pt is bottom right, pivot is top left.
    else
    {
        QRectF temp(pivot, secondPt);
        return temp;
    }

}


void Model::frameRequested()
{
    if(frames.size() <= 1 && firstImage)
    {
        emit sendPreview(currentImage);
    }
    else if(currentFrame == frames.size())
    {
        emit sendPreview(currentImage);
        currentFrame = 0;
    }
    else if(currentFrame <= frames.size()-1)
    {

        emit sendPreview(frames[currentFrame]);
        currentFrame++;
    }
    else
    {
        currentFrame = 0;
        emit sendPreview(frames[currentFrame]);
    }

}

void Model::addToFrames()
{
    if(frames.size()==1 && firstImage)
    {
        frames[0] = currentImage;
        firstImage = false;
    }
    else
    {
        frames.push_back(currentImage);
    }

}

void Model::undoAction()
{

}

void Model::redoAction()
{

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

//void Model::fillZone(QPoint coords) {

//    if(validPixel(coords))
//    {
//        colorBeingFilled = currentImage.pixelColor(coords);
//        fillPixel(coords, 0);
//    }
//}

//void Model::fillPixel(QPoint coords, int direction) {

//    fillCount++;
//    int px = coords.rx();
//    int py = coords.ry();

//    //if((px >=0 && px < 100) && (py >= 0 && py < 100)){
//        QColor currColor = currentImage.pixelColor(coords);

//        if((currColor == colorBeingFilled) && (colorBeingFilled != currentColor)){

//            currentImage.setPixelColor(coords, currentColor);
//            fillCountTwo++;


//        if(px > 0 && direction != 2)
//        {
//            QPoint point1(px - 1, py);
//            fillPixel(point1, 1);
//        }
//        if(px < 99 && direction != 1)
//        {
//            QPoint point2(px + 1, py);
//            fillPixel(point2, 2);
//        }
//        if(py > 0 && direction != 4)
//        {
//            QPoint point3(px, py - 1);
//            fillPixel(point3, 3);
//        }
//        if(py < 99 && direction != 3)
//        {
//            QPoint point4(px, py + 1);
//            fillPixel(point4, 4);
//        }

//        }
//    //}

//}

void Model::fill(QPoint coords) {
    if(!validPixel(coords))
        return;
    QColor colorBeingFilled = currentImage.pixelColor(coords);
    if (colorBeingFilled == currentColor)
        return;
    currentImage.setPixelColor(coords, currentColor);


    std::queue<QPoint> que;
    que.push(coords);
    while(!que.empty()) {
        const QPoint& point = que.front();
        que.pop();

        int px = point.x();
        int py = point.y();

        QPoint points[4];
        points[0] = QPoint(px - 1, py);
        points[1] = QPoint(px + 1, py);
        points[2] = QPoint(px, py - 1);
        points[3] = QPoint(px, py + 1);

        for (int i = 0; i < 4; i++) {
            if (validPixel(points[i])) {
                QColor pointColor = currentImage.pixelColor(points[i]);
                if(pointColor == colorBeingFilled) {
                    currentImage.setPixelColor(points[i], currentColor);
                    que.push(points[i]);
                }
            }
        }
    }
}
bool Model::validPixel(QPoint coords){
    int px = coords.rx();
    int py = coords.ry();

    if(px<0 || px >= 100 || py < 0 || py >= 100){
        return false;
    }
    return true;
}

void Model::drawShapePreview(QMouseEvent *e)
{
    if(activePreview)
    {
        QImage tempIm = currentImage;
        QPainter tempPaint(&tempIm);
        tempPaint.setPen(currentColor);
        QPointF firstPt(shapeCoordX, shapeCoordY);
        QPointF secondPt(e->pos().x()/xScale, e->pos().y()/yScale);
        if(currentTool == 4)
        {
            tempPaint.drawLine(firstPt, secondPt);
        }
        else if(currentTool == 5)
        {
            tempPaint.drawRect(getRectangle(firstPt, secondPt));
        }
        else if(currentTool == 6)
        {
            tempPaint.drawEllipse(getRectangle(firstPt, secondPt));
        }


        emit redrawImage(tempIm);



    }
    else
    {

        activePreview = true;

        shapeCoordX = e->pos().x() / xScale;
        shapeCoordY = e->pos().y() / yScale;

        //emit redrawImage(currentImage);
    }
}

//All tool selection slots go here.

void Model::colorOpen()
{
    QColor penColor =  QColorDialog::getColor(Qt::white,nullptr,"Choose Color");
    currentColor = penColor;
    painter.setPen(penColor);
    painter.setBrush(Qt::NoBrush);
}


void Model::penSelected()
{
    painter.setPen(currentColor);
    currentTool = 0;

}

void Model::lineSelected()
{
    //want to set activePreview to false to begin this tool.
    activePreview = false;

    //Want to set pen back to currentColor if it was changed by erase tool.
    painter.setPen(currentColor);

    currentTool = 4;

}

void Model::rectSelected()
{
    //want to set activePreview to false to begin this tool.
    activePreview = false;

    //Want to set pen back to currentColor if it was changed by erase tool.
    painter.setPen(currentColor);

    currentTool = 5;
}
void Model::ellipseSelected()
{
    //want to set activePreview to false to begin this tool.
    activePreview = false;

    //Want to set pen back to currentColor if it was changed by erase tool.
    painter.setPen(currentColor);

    currentTool = 6;
}

void Model::eraseSelected()
{
    //Just using pen tool and setting pen color to gray but not changing currentColor variable.
    painter.setPen(Qt::gray);
    currentTool = 0;
}
void Model::fillSelected()
{
    //Want to set pen back to currentColor if it was changed by erase tool.
    painter.setPen(currentColor);
    currentTool = 3;
}

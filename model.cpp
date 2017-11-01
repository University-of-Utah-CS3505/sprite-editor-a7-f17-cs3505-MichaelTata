#include "model.h"
#include <iostream>


Model::Model(QObject *parent) : QObject(parent), currentImage(100, 100, QImage::Format_ARGB32)
{
    //Temporary default value as we use 500,500 for default image
    xScale = 5;
    yScale = 5;


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
    //Left mouse button click or click+hold+drag?
    if(e->buttons() == Qt::LeftButton)
    {
        //Switch-case here for all tools?
        switch(currentTool) {
        case 0:


            int tempX = e->pos().x() / xScale;

            int tempY = e->pos().y() / yScale;


            //Make sure we only allow ~25 or so undo otherwise program crashes
            //undoes.push_back(currentImage);
            painter.drawPoint(tempX, tempY);
            emit redrawImage(currentImage);
            break; 


        }
    }   
}


void Model::rescale()
{
    int t = 2;
    //xScale = temp.width()/100;
    // yScale = temp.height()/100;
    xScale *= 2;
    yScale *= 2;

    emit sendRescale(2);


}

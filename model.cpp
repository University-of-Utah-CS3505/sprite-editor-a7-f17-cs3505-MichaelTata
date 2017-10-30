#include "model.h"



Model::Model(QObject *parent) : QObject(parent)
{
    //Default value until we add load and creation of custom sized sprite
    currentImage = QPixmap(600, 480).toImage();
    currentImage.fill(Qt::gray);

    currentTool = 0;

    painter.begin(&currentImage);
    //Default pen of black.
    painter.setPen(Qt::black);

    //painter.end();
    emit redrawImage(currentImage);

}

//Slot to receive a drawing event. Used Specifically for when a click(or unclick) has occurred
void Model::manipulateImage(QMouseEvent *e)
{
    //Left mouse button click or click+hold+drag?
    if(e->buttons() == Qt::LeftButton)
    {
        //Switch-case here for all tools?
        if(currentTool == 0)
        {
            int tempX = e->pos().x();
            int tempY = e->pos().y();

            //Make sure we only allow ~25 or so undo otherwise program crashes
            //undoes.push_back(currentImage);
            painter.drawPoint(tempX, tempY);
            emit redrawImage(currentImage);
        }
    }
}

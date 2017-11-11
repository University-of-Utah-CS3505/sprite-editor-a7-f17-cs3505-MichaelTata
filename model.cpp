#include "model.h"

Model::Model(QObject *parent) : QObject(parent), currentImage(100, 100, QImage::Format_ARGB32) {
    //Temporary default value as we use 500,500 for default image
    xScale = 1;
    yScale = 1;

    firstImage = true;
    currentPreviewFrame = 0;
    currentColor = Qt::black;
    currentFrame = 0;

    //currentImage(64, 64, QImage::Format_ARGB32);
    //Default value until we add load and creation of custom sized sprite
    //currentImage = QPixmap(64, 64).toImage();
    currentImage.fill(Qt::transparent);

    frames.push_back(currentImage);
    std::tuple<std::vector<QImage>, int> tempTuple (frames, 0);
    undoes.push_back(tempTuple);

    currentTool = 0;

    painter.begin(&currentImage);

    painter.setPen(currentColor);

    emit redrawImage(currentImage);
}

void Model::createNewSprite(int w, int h)
{
    painter.end();

    frames.clear();
    undoes.clear();
    redoes.clear();


    xScale = 1;
    yScale = 1;

    currentImage = QImage(w, h, QImage::Format_ARGB32);

    currentTool = 0;

    firstImage = true;
    currentPreviewFrame = 0;
    currentColor = Qt::black;
    currentFrame = 0;

    currentImage.fill(Qt::transparent);

    painter.begin(&currentImage);

    painter.setPen(currentColor);

    frames.push_back(currentImage);
    std::tuple<std::vector<QImage>, int> tempTuple (frames, 0);
    undoes.push_back(tempTuple);


    QString style = "background-color : rgb(%1, %2, %3); border: none;";
    emit showColor(style.arg(0).arg(0).arg(0));

    emit sendNewInfo(w, h);

    emit redrawImage(currentImage);

}


//Slot for released mouse click event. So if we have a shape/line tool chosen
//This will add the actual shape to the image. This is needed as manipulate image only handles
//Previews, as the mouse event cannot be used to determine mouse button release, only move and click/drag
void Model::addShapeToImage(QMouseEvent *e, int horScroll, int verScroll) {
    QPointF firstPt(shapeCoordX, shapeCoordY);
    QPointF secondPt((e->pos().x()/xScale)+horScroll, (e->pos().y()/yScale)+verScroll);
    QRectF tempRec = getRectangle(firstPt, secondPt);
    switch(currentTool) {
        case 0:
            updateFrames();
        break;

        case 1:
            updateFrames();
        break;

        case 3:
            updateFrames();
        break;

        case 4:
            painter.drawLine(firstPt, secondPt);      
            emit redrawImage(currentImage);
            updateFrames();
        break;

        case 5:
            painter.drawRect(tempRec);
            emit redrawImage(currentImage);
            updateFrames();
        break;

        case 6:
            painter.drawEllipse(tempRec);         
            emit redrawImage(currentImage);
            updateFrames();
        break;
    }
    activePreview = false;
}

//Slot to receive a drawing event. Used Specifically for when a click(or unclick) has occurred
void Model::manipulateImage(QMouseEvent *e, int horScroll, int verScroll) {
    //qDebug() << "manipulating";
    int tempX = (e->pos().x() / xScale) + horScroll;
    int tempY = (e->pos().y() / yScale) + verScroll;
    QPoint point(tempX, tempY);

    //Left mouse button click or click+hold+drag?
    if(e->buttons() == Qt::LeftButton) {
        switch(currentTool) {
        case 0:
            //Make sure we only allow ~25 or so undo otherwise program crashes
            //undoes.push_back(currentImage);
            painter.drawPoint(point);
            emit redrawImage(currentImage);
            break;

         case 1:
            if(validPixel(point)) {
                currentImage.setPixelColor(point, Qt::transparent);
                emit redrawImage(currentImage);
            }
            break;

        case 3:
            fill(point);
            emit redrawImage(currentImage);
            break;

        case 4:
            drawShapePreview(e, horScroll, verScroll);
            break;

         case 5:
            drawShapePreview(e, horScroll, verScroll);
            break;

        case 6:
           drawShapePreview(e, horScroll, verScroll);
           break;

        case 7:
            if(validPixel(point)) {
                changeColor(currentImage.pixelColor(point));
            }
            break;
        }
    }
    else if (validPixel(point)) {
        emit sendHighlight(point);
    }
}

QRectF Model::getRectangle(QPointF pivot, QPointF secondPt) {
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
    // Second pt is bottom left of rect, pivot is top right.
    else if(secondPt.x() < pivot.x() && secondPt.y() > pivot.y())
    {
        QRectF temp;
        temp.setBottomLeft(secondPt);
        temp.setTopRight(pivot);
        return temp;
    }
    //Second pt is bottom right, pivot is top left.
    else
    {
        QRectF temp(pivot, secondPt);
        return temp;
    }
}

void Model::frameRequested()
{
    if(currentPreviewFrame == frames.size() - 1){
        emit sendPreview(frames[currentPreviewFrame]);
        currentPreviewFrame = 0;
    }
    else if(currentPreviewFrame > frames.size()-1)
    {
        currentPreviewFrame = 0;
    } else {
        emit sendPreview(frames[currentPreviewFrame]);
        currentPreviewFrame++;
    }
}

void Model::addToFrames() {

    frames.push_back(frames.back());
    currentFrame = frames.size() - 1;
    std::tuple<std::vector<QImage>, int> tempTuple (frames, currentFrame);
    undoes.push_back(tempTuple);
    redoes.clear();
    currentPreviewFrame = 0;

    emit setMaxScroll(frames.size() - 1);
    emit setScrollPosition(currentFrame);


}

void Model::deleteFromFrames() {
    if(currentFrame == 0 && frames.size() == 1) {
        return;
    }

    std::tuple<std::vector<QImage>, int> tempTuple (frames, currentFrame);
    undoes.push_back(tempTuple);
    frames.erase(frames.begin() + currentFrame);
    redoes.clear();
    currentPreviewFrame = 0;

    if(currentFrame != 0) {
        currentFrame -= 1;
    }

    recalcCurrentImage();
    emit setMaxScroll(frames.size() - 1);
    emit setScrollPosition(currentFrame);
    emit redrawImage(currentImage);

}
void Model::changeFrame(int currFrame){
    currentFrame = currFrame;
    recalcCurrentImage();

    emit redrawImage(currentImage);
}
void Model::updateFrames(){
    if(frames[currentFrame] != currentImage) {
        frames[currentFrame] = currentImage;
        std::tuple<std::vector<QImage>, int> tempTuple(frames, currentFrame);
        undoes.push_back(tempTuple);
        redoes.clear();
    }

}
void Model::undoAction() {

    if(undoes.size() > 1) {
        redoes.push_back(undoes.back());
        undoes.pop_back();

        frames = std::get<0>(undoes.back());

        if(std::get<1>(redoes.back()) < currentFrame) {
            currentFrame = std::get<1>(redoes.back());
        }
        else {
            currentFrame = std::get<1>(undoes.back());
        }

        recalcCurrentImage();
        emit redrawImage(currentImage);
        emit setMaxScroll(frames.size() - 1);
        emit setScrollPosition(currentFrame);
    }
}

void Model::redoAction() {
    if(redoes.size() > 0) {
        undoes.push_back(redoes.back());
        redoes.pop_back();
        frames = std::get<0>(undoes.back());
        currentFrame = std::get<1>(undoes.back());

        recalcCurrentImage();
        emit redrawImage(currentImage);
        emit setMaxScroll(frames.size() - 1);
        emit setScrollPosition(currentFrame);
    }
}


void Model::recalcCurrentImage() {
        painter.end();
        currentImage = frames[currentFrame];
        painter.begin(&currentImage);
        painter.setPen(currentColor);
}

void Model::open() {
QString fileName = QFileDialog::getOpenFileName();
    QFile file(fileName);
    qreal r = 0, g = 0, b = 0, a = 0;
    int framesSize;
    frames.clear();
    do{
        if(file.open(QIODevice::ReadOnly)){
            std::ifstream in(fileName.toStdString());
            in >> framesSize;
            for(int i=0; i < framesSize; i++){
                for(int y=0; y < currentImage.height(); y++){
                    for(int x=0; x < currentImage.width(); x++){
                        QPoint coords(x,y);
                        in >> r >> g >> b >> a;
                        QColor color(r, g, b, a);
                        currentImage.setPixelColor(coords, color);
                    }
                }
                addToFrames();
            }
        }

        file.close();
    } while (file.isOpen());
    emit redrawImage(frames[0]);
}

void Model::save() {
    QString fileName = QFileDialog::getSaveFileName();
    QFile file(fileName);
    QString str;
    qreal r = 0, b = 0, g = 0, a = 0;
    if(file.open(QIODevice::WriteOnly)){
        std::ofstream out(fileName.toStdString());
        qDebug() << frames;
        out << frames.size() << " ";
        for(auto i = frames.begin(); i != frames.end(); ++i){
            //auto saveFrame = frames[i];
            for(int y=0; y < currentImage.height(); y++){
                for(int x=0; x < currentImage.width(); x++){
                    i->pixelColor(x,y).getRgbF(&r, &g, &b, &a);
                    str = str.number(r*255) + " " + str.number(g*255) + " " + str.number(b*255) + " " + str.number(a*255) + " ";
                    out << str.toStdString();
                }
                str.clear();
                out << "\n";
            }
        }
    }
    file.close();
}

void Model::exportToGif() {

}




void Model::scaleOut() {
    xScale/=2;
    yScale/=2;
    emit sendScaleOut(2);
}


void Model::scaleIn() {
    xScale *= 2;
    yScale *= 2;
    emit sendScaleIn(2);
}

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
bool Model::validPixel(QPoint coords) {
    int px = coords.rx();
    int py = coords.ry();

    if(px < 0 || px >= currentImage.width() || py < 0 || py >= currentImage.height()) {
        return false;
    }
    return true;
}

void Model::drawShapePreview(QMouseEvent *e, int horScroll, int verScroll) {
    if(activePreview)
    {
        QImage tempIm = currentImage;
        QPainter tempPaint(&tempIm);
        tempPaint.setPen(currentColor);
        QPointF firstPt(shapeCoordX, shapeCoordY);
        QPointF secondPt((e->pos().x()/xScale)+horScroll, (e->pos().y()/yScale)+verScroll);
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
        shapeCoordX = (e->pos().x() / xScale)+horScroll;
        shapeCoordY = (e->pos().y() / yScale)+verScroll;
    }
}

void Model::changeColor(QColor penColor) {
    currentColor = penColor;
    if(currentTool != 1){
         painter.setPen(penColor);
         painter.setBrush(Qt::NoBrush);
    }
    QString style = "background-color : rgb(%1, %2, %3); border: none;";
    emit showColor(style.arg(penColor.red()).arg(penColor.green()).arg(penColor.blue()));
}

//All tool selection slots go here.
void Model::colorOpen() {
    changeColor(QColorDialog::getColor(Qt::white,nullptr,"Choose Color"));
}


void Model::penSelected() {
    painter.setPen(currentColor);
    currentTool = 0;
}

void Model::lineSelected() {
    //want to set activePreview to false to begin this tool.
    activePreview = false;

    //Want to set pen back to currentColor if it was changed by erase tool.
    painter.setPen(currentColor);

    currentTool = 4;

}

void Model::rectSelected() {
    //want to set activePreview to false to begin this tool.
    activePreview = false;

    //Want to set pen back to currentColor if it was changed by erase tool.
    painter.setPen(currentColor);

    currentTool = 5;
}

void Model::ellipseSelected() {
    //want to set activePreview to false to begin this tool.
    activePreview = false;

    //Want to set pen back to currentColor if it was changed by erase tool.
    painter.setPen(currentColor);

    currentTool = 6;
}

void Model::eraseSelected() {
    currentTool = 1;
}

void Model::fillSelected() {
    //Want to set pen back to currentColor if it was changed by erase tool.
    painter.setPen(currentColor);
    currentTool = 3;
}

void Model::colorpickerSelected() {
    currentTool = 7;
}

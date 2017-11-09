#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QImage>
#include <QColor>
#include <vector>
#include <QSize>
#include <QPainter>
#include <QColorDialog>
#include <QFileDialog>
#include <QMouseEvent>
#include <QPoint>
#include <iostream>
#include <QDebug>
#include <queue>

class Model : public QObject
{
    Q_OBJECT
private:
    // frames will contain all of the frames, or images, of the current project.
    std::vector<QImage> frames;
    // undoes and redoes hold the different states of the current image
    // and allow for them to be undone or redone.
    std::vector<std::vector<QImage>> undoes;
    std::vector<std::vector<QImage>> redoes;
    // The view will show the current image and it is the only image
    // that can be worked on at a time.
    QImage currentImage;
    /* The current tool directs how the image will be manipulated.
     * An encoding for the tools would work best to distinguish them
     * from each other.
     * The encoding is the following:
     * 0 = pen
     * 1 = erase
     * 2 = select
     * 3 = fill
     * 4 = line
     * 5 = rectangle
     * 6 = oval
     * 7 = color picker
     * Add more tools as needed.
     */

    //This is used to keep track of what frame we are currently
    //sending to be previewed.
    int currentPreviewFrame;

    //This is used to keep track of cwhat frame you are currently editing.
    int currentFrame;



    int currentTool;
    double xScale;
    double yScale;

    //These variables are used exclusively for drawing shapes/lines.
    //We need the starting coord and to know when we are making a shape, this way we can make a preview.
    int shapeCoordX;
    int shapeCoordY;
    bool activePreview;

    QColor currentColor;
    QColor colorBeingFilled;
    QPointF currentPoint;

    QPainter painter;
    QColorDialog colorPicker;
    // This file dialog will handle creating a new project, saving, loading, and exporting a gif.
    QFileDialog fileDia;

    //Used to temporarily get around the flicker on preview.
    //As the first image needs to be added before drawing so we have a blank image in our frames
    bool firstImage;

    QRectF getRectangle(QPointF, QPointF);
    void changeColor(QColor);


public:
    explicit Model(QObject *parent = 0);
protected:
//    void fillZone(QPoint);
//    void fillPixel(QPoint, int direction);
    bool validPixel(QPoint);
    void drawShapePreview(QMouseEvent *e);
    void fill(QPoint);
    void updateFrames();
    void recalcCurrentImage();
signals:
    void redrawImage(QImage&);

    //Sends image to preview to be displayed
    void sendPreview(QImage&);

    void sendScaleIn(int);

    void sendScaleOut(int);

    void sendHighlight(QPoint);

    void showColor(QString);

    void setMaxScroll(int);




public slots:
    void manipulateImage(QMouseEvent *e);

    void addShapeToImage(QMouseEvent *e);

    void changeFrame(int);

    void scaleIn();

    void scaleOut();

    void colorOpen();

    void penSelected();

    void rectSelected();

    void lineSelected();

    void fillSelected();

    void ellipseSelected();

    void eraseSelected();

    void colorpickerSelected();

    void frameRequested();

    void addToFrames();

    void undoAction();

    void redoAction();


};

#endif // MODEL_H

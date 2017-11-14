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
#include <fstream>
#include <tuple>
#include <QBuffer>

using namespace std;

class Model : public QObject {
    Q_OBJECT
private:
    // frames will contain all of the frames, or images, of the current project.
    std::vector<QImage> frames;

    // undoes and redoes hold the different states of the current image
    // and allow for them to be undone or redone.
    std::vector<std::tuple<std::vector<QImage>, int>> undoes;
    std::vector<std::tuple<std::vector<QImage>, int>> redoes;
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

    // This is used to keep track of what frame we are currently
    // sending to be previewed.
    int currentPreviewFrame;

    // This is used to keep track of cwhat frame you are currently editing.
    int currentFrame;

    // This currentTool variable holds the integer that defines what tool is currently being used.
    int currentTool;

    // These scale variables handle the scaling for the zoom function.
    double xScale;
    double yScale;

    // These variables are used exclusively for drawing shapes/lines.
    // We need the starting coord and to know when we are making a shape, this way we can make a preview.
    int shapeCoordX;
    int shapeCoordY;
    bool activePreview;

    // These variables capture what color we have chosen, and the color being filled for fill tool.
    QColor currentColor;
    QColor colorBeingFilled;

    // This is the current painter object being used and a dialog for the color picker.
    QPainter painter;
    QColorDialog colorPicker;

    // This file dialog will handle creating a new project, saving, loading, and exporting a gif.
    QFileDialog fileDia;

    // Used to temporarily get around the flicker on preview.
    // As the first image needs to be added before drawing so we have a blank image in our frames
    bool firstImage;

    // Used to determine whether or not we used new or load when creating a sprite
    // So we can know whether or not to add an initial frame.
    bool loadingImage;

    // This boolean means if we have just most recently undid a delete frame rather than any other action.
    bool undidDeleteFrame = false;

    // This QRectF object holds the current working rectangle for a draw image.
    QRectF getRectangle(QPointF, QPointF);

<<<<<<< HEAD
=======
    void changeColor(QColor);



    int framerate;


>>>>>>> e09e80ff1d133c3b8d24dfb3931fe85c0e26ed35
public:
    explicit Model(QObject* parent = 0);

protected:
    // This method returns true if the pixel being pointed at is in the matrix dimensions.
    bool validPixel(QPoint);

    // This method is a preview for the shape about to be drawn, while the mouse is held down
    // And not when the mouse click is unclicked.
    void drawShapePreview(QMouseEvent* e,int,int);

    // This method handles the fill tool.
    void fill(QPoint);

    // This method updates frames when an action is done that is capable of being redone in the
    // Redo feature.
    void updateFrames();

    // This method redraws the current image on the current frame.
    void recalcCurrentImage();

    // This method emits a redraw single and updates the frame.
    void redrawImageF();

    // This method changes the color of the pen and current color.
    void changeColor(QColor);

signals:
    // This signal redraws the current image.
    void redrawImage(QImage&);

    // Sends image to preview to be displayed.
    void sendPreview(QImage&);

    // This signal scales the image in for the zoom in feature.
    void sendScaleIn(int);

    // This signal scales the image in for the zoom out feature.
    void sendScaleOut(int);

    // This signal highlights the current pixel being pointed at by the cursor.
    void sendHighlight(QPoint);

    // This signal shows the correct color on the color bar.
    void showColor(QString);

    // This signal sets the maximum valie for the scroll bar.
    void setMaxScroll(int);

    // This signal sets the position of the scroll bar.
    void setScrollPosition(int);

    // This signal works with creating a new drawing board's dimensions.
    void sendNewInfo(int, int);

    // This signal sends the image to the middle preview screen.
    void sendPreviewMid(QImage&);

    // This signal sends the image to the left preview screen.
    void sendPreviewLeft(QImage&);

    // This signal sends the image to the right preview screen.
    void sendPreviewRight(QImage&);

public slots:
    // This slow deals with creating a new sprite for both new and load features.
    void createNewSprite(int, int);

    // This slot deals with manipulating image through mouse clicks and drags.
    void manipulateImage(QMouseEvent* e, int, int);

    // This slot deals with adding a shape to the image when the mouse is unclicked.
    void addShapeToImage(QMouseEvent* e, int, int);

    // This slot changes the current frame being worked on using currentFrame variable.
    void changeFrame(int);

    // This slot deals with zooming in.
    void scaleIn();

    // This slot deals with zooming out.
    void scaleOut();

    // This slot deals with opening the color dialog box.
    void colorOpen();

    // This slot deals with selecting the pen tool.
    void penSelected();

    // This slot deals with selecting the rectangle tool.
    void rectSelected();

    // This slot deals with selecting the line tool.
    void lineSelected();

    // This slot deals with selecting the fill tool.
    void fillSelected();

    // This slot deals with selecting the ellipse tool.
    void ellipseSelected();

    // This slot deals with selecting the erase tool.
    void eraseSelected();

    // This slot deals with selecting the color picker feature.
    void colorpickerSelected();

    // This slot deals with the preview frames feature.
    void frameRequested();

    // This slot deals with adding an extra frame.
    void addToFrames();

    // This slot deals with deleting a frame.
    void deleteFromFrames();

    // This slot deals with undoing an action.
    void undoAction();

    void redoAction();
    void open();
    void save();
    void exportToGif();
    void changeFramerate(int);


};

#endif // MODEL_H

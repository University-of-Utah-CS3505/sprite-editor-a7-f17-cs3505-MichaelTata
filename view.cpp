#include "view.h"
#include "ui_view.h"

View::View(Model* m, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::View)
{
    ui->setupUi(this);

    //Connection to redraw the board. Model sends new image to be drawn to drawing widget.
    connect(m, &Model::redrawImage, ui->drawingBoard, &DrawingWidget::drawUpdatedImage);

    //Connection from a drawing board click to an image manipulation in the model.
    connect(ui->drawingBoard, &DrawingWidget::click, m, &Model::manipulateImage);

    connect(ui->drawingBoard, &DrawingWidget::mouseMove, m, &Model::manipulateImage);

    connect(ui->zoomInButton, &QPushButton::clicked, m, &Model::scaleIn);

    connect(ui->zoomOutButton, &QPushButton::clicked, m, &Model::scaleOut);



    connect(m, &Model::sendScaleIn, ui->drawingBoard, &DrawingWidget::scaleIn);

    connect(m, &Model::sendScaleOut, ui->drawingBoard, &DrawingWidget::scaleOut);

    connect(m, &Model::sendHighlight, ui->drawingBoard, &DrawingWidget::highlightPixel);


    connect(ui->drawingBoard, &DrawingWidget::unclick, m, &Model::addShapeToImage);







    connect(ui->penButton, &QPushButton::clicked, m, &Model::penSelected);

    connect(ui->lineButton, &QPushButton::clicked, m, &Model::lineSelected);



}
View::~View()
{
    delete ui;
}

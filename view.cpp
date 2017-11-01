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

    connect(ui->ZoomInButton, &QPushButton::clicked, m, &Model::scaleIn);

    connect(ui->ZoomOutButton, &QPushButton::clicked, m, &Model::scaleOut);



    connect(m, &Model::sendScaleIn, ui->drawingBoard, &DrawingWidget::scaleIn);

    connect(m, &Model::sendScaleOut, ui->drawingBoard, &DrawingWidget::scaleOut);

    connect(m, &Model::sendHighlight, ui->drawingBoard, &DrawingWidget::highlightPixel);


}
View::~View()
{
    delete ui;
}

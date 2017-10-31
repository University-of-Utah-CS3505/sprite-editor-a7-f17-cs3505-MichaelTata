#include "view.h"
#include "ui_view.h"

View::View(Model* m, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::View)
{
    ui->setupUi(this);

    //Connection to redraw the board. Model sends new image to be drawn to drawing widget.
    connect(m, &Model::redrawImage, ui->drawingBoard, &DrawingWidget::drawImage);

    //Connection from a drawing board click to an image manipulation in the model.
    connect(ui->drawingBoard, &DrawingWidget::click, m, &Model::manipulateImage);

    connect(ui->drawingBoard, &DrawingWidget::mouseMove, m, &Model::manipulateImage);

    connect(ui->drawingBoard, &DrawingWidget::rescale, m, &Model::rescale);

}
View::~View()
{
    delete ui;
}

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

    //Connection to fill an area.

    connect(ui->drawingBoard, &DrawingWidget::mouseMove, m, &Model::manipulateImage);

    connect(ui->zoomInButton, &QPushButton::clicked, m, &Model::scaleIn);

    connect(ui->zoomOutButton, &QPushButton::clicked, m, &Model::scaleOut);

    connect(ui->colorbutton, &QPushButton::clicked, m, &Model::colorOpen);

    connect(ui->undoButton, &QPushButton::clicked, m, &Model::undoAction);

    connect(m, &Model::showColor, ui->colorview, &QLabel::setStyleSheet);

    connect(m, &Model::sendScaleIn, ui->drawingBoard, &DrawingWidget::scaleIn);

    connect(m, &Model::sendScaleOut, ui->drawingBoard, &DrawingWidget::scaleOut);

    connect(m, &Model::sendHighlight, ui->drawingBoard, &DrawingWidget::highlightPixel);


    connect(ui->drawingBoard, &DrawingWidget::unclick, m, &Model::addShapeToImage);


    frameTimer = new QTimer(this);
    connect(frameTimer, SIGNAL(timeout()), m, SLOT(frameRequested()));
    frameTimer->start(1000/ui->fpsSlider->value());

    ui->previewWidget->scaleIn(2);

    connect(ui->fpsSlider, &QSlider::valueChanged, this, &View::fpsChange);

    connect(ui->addFrameButton, &QPushButton::clicked, m, &Model::addToFrames);

    connect(ui->penButton, &QPushButton::clicked, m, &Model::penSelected);

    connect(ui->lineButton, &QPushButton::clicked, m, &Model::lineSelected);

    connect(ui->fillButton, &QPushButton::clicked, m, &Model::fillSelected);

    connect(ui->rectangleButton, &QPushButton::clicked, m, &Model::rectSelected);
    connect(ui->ellipseButton, &QPushButton::clicked, m, &Model::ellipseSelected);
    connect(ui->eraseButton, &QPushButton::clicked, m, &Model::eraseSelected);
    connect(ui->cpButton, &QPushButton::clicked, m, &Model::colorpickerSelected);
    connect(m, &Model::sendPreview, ui->previewWidget, &DrawingWidget::drawUpdatedImage);


}

void View::fpsChange(int change)
{

    frameTimer->stop();
    frameTimer->start(1000/change);
}

View::~View()
{
    delete ui;
}

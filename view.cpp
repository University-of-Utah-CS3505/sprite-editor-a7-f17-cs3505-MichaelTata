#include "view.h"
#include "ui_view.h"


View::View(Model* m, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::View)
{
    ui->setupUi(this);

    newSprite = new CreateNewSprite();

    //has to be done here to color the tools box. Unless you want to start by calling whiteTheme();.
    ui->groupBox->setStyleSheet("background-color: rgb(230, 230, 230);");
    //ui->groupBox2->setStyleSheet("background-color: rgb(230, 230, 230);");













    connect(ui->actionNew, &QAction::triggered, this, &View::openNewSpriteWindow);

    //Connection from createnewsprite window, which will send size info to drawing board and model.

    connect(m, &Model::sendNewInfo, ui->drawingBoard, &DrawingWidget::createNewBoard);

    //Connection to model to create a new sprite
    connect(newSprite, &CreateNewSprite::sendSpriteInfo, m, &Model::createNewSprite);




    connect(ui->actionLoad, &QAction::triggered, m, &Model::open);

    connect(ui->actionSave, &QAction::triggered, m, &Model::save);
    connect(ui->actionExport_to_Gif, &QAction::triggered, m, &Model::exportToGif);


    //Connection to redraw the board. Model sends new image to be drawn to drawing widget.
    connect(m, &Model::redrawImage, ui->drawingBoard, &DrawingWidget::drawUpdatedImage);

    //Connection from a drawing board click to an image manipulation in the model.
    connect(ui->drawingBoard, &DrawingWidget::click, m, &Model::manipulateImage);

    //Connection from model to scrollbar
    connect(m, &Model::setMaxScroll, ui->previewscrollbar, &QScrollBar::setMaximum);
    connect(m, &Model::setScrollPosition, ui->previewscrollbar, &QScrollBar::setValue);
    connect(ui->previewscrollbar, &QScrollBar::valueChanged, m, &Model::changeFrame);

    connect(ui->previewscrollbar, &QScrollBar::valueChanged, m, &Model::changeFramerate);

    //Connection to fill an area.

    connect(ui->drawingBoard, &DrawingWidget::mouseMove, m, &Model::manipulateImage);

    connect(ui->zoomInButton, &QPushButton::clicked, m, &Model::scaleIn);

    connect(ui->zoomOutButton, &QPushButton::clicked, m, &Model::scaleOut);

    connect(ui->colorButton, &QPushButton::clicked, m, &Model::colorOpen);

    connect(ui->undoButton, &QPushButton::clicked, m, &Model::undoAction);

    connect(ui->redoButton, &QPushButton::clicked, m, &Model::redoAction);

    connect(m, &Model::showColor, ui->colorButton, &QPushButton::setStyleSheet);

    connect(m, &Model::sendScaleIn, ui->drawingBoard, &DrawingWidget::scaleIn);

    connect(m, &Model::sendScaleOut, ui->drawingBoard, &DrawingWidget::scaleOut);

    connect(m, &Model::sendHighlight, ui->drawingBoard, &DrawingWidget::highlightPixel);


    connect(ui->drawingBoard, &DrawingWidget::unclick, m, &Model::addShapeToImage);


    frameTimer = new QTimer(this);
    connect(frameTimer, SIGNAL(timeout()), m, SLOT(frameRequested()));
    frameTimer->start(1000/ui->fpsSlider->value());


    //Changes here for preview widget....
    ui->previewWidget->scaleIn(2);



    connect(ui->fpsSlider, &QSlider::valueChanged, this, &View::fpsChange);

    connect(ui->addFrameButton, &QPushButton::clicked, m, &Model::addToFrames);
    connect(ui->deleteFrameButton, &QPushButton::clicked, m, &Model::deleteFromFrames);

    connect(ui->penButton, &QPushButton::clicked, m, &Model::penSelected);

    connect(ui->lineButton, &QPushButton::clicked, m, &Model::lineSelected);

    connect(ui->fillButton, &QPushButton::clicked, m, &Model::fillSelected);

    connect(ui->rectangleButton, &QPushButton::clicked, m, &Model::rectSelected);
    connect(ui->ellipseButton, &QPushButton::clicked, m, &Model::ellipseSelected);
    connect(ui->eraseButton, &QPushButton::clicked, m, &Model::eraseSelected);
    connect(ui->cpButton, &QPushButton::clicked, m, &Model::colorpickerSelected);
    connect(m, &Model::sendPreview, ui->previewWidget, &DrawingWidget::drawUpdatedImage);
    connect(m, &Model::sendPreviewMid, ui->previewWidgetMid, &DrawingWidget::drawUpdatedImage);
    connect(m, &Model::sendPreviewLeft, ui->previewWidgetLeft, &DrawingWidget::drawUpdatedImage);
    connect(m, &Model::sendPreviewRight, ui->previewWidgetRight, &DrawingWidget::drawUpdatedImage);

    //Themes
    connect(ui->actionBlack, &QAction::triggered, this, &View::themeBlack);
    connect(ui->actionWhite, &QAction::triggered, this, &View::themeWhite);

    //ScrollBar changes to signal drawingboard shift
    connect(ui->horizontalScrollBar, &QScrollBar::valueChanged, ui->drawingBoard, &DrawingWidget::scrollHor);
    connect(ui->verticalScrollBar, &QScrollBar::valueChanged, ui->drawingBoard, &DrawingWidget::scrollVer);


}


void View::openNewSpriteWindow()
{
    ui->horizontalScrollBar->setValue(0);
    ui->verticalScrollBar->setValue(0);
    newSprite->show();
}

void View::fpsChange(int change)
{

    frameTimer->stop();
    frameTimer->start(1000/change);
}

void View::themeBlack(){
    this->setStyleSheet("background-color: rgb(20, 20, 20);");
    ui->fillButton->setStyleSheet("background-color: rgb(20, 20, 20);");
    ui->penButton->setStyleSheet("background-color: rgb(20, 20, 20);");
    ui->rectangleButton->setStyleSheet("background-color: rgb(20, 20, 20);");
    ui->eraseButton->setStyleSheet("background-color: rgb(20, 20, 20);");
    ui->ellipseButton->setStyleSheet("background-color: rgb(20, 20, 20);");
    ui->cpButton->setStyleSheet("background-color: rgb(20, 20, 20); color: white");
    ui->lineButton->setStyleSheet("background-color: rgb(20, 20, 20);");
    ui->undoButton->setStyleSheet("background-color: rgb(20, 20, 20);");
    ui->redoButton->setStyleSheet("background-color: rgb(20, 20, 20);");
    ui->zoomOutButton->setStyleSheet("background-color: rgb(20, 20, 20);");
    ui->zoomInButton->setStyleSheet("background-color: rgb(20, 20, 20);");
    ui->addFrameButton->setStyleSheet("background-color: rgb(50, 50, 50); color: white");
    ui->previewscrollbar->setStyleSheet("background-color: rgb(50, 50, 50);");
    ui->mainToolBar->setStyleSheet("background-color: rgb(50, 50, 50);");
    ui->menuBar->setStyleSheet("background-color: rgb(20, 20, 20); color: white");
    ui->menuFile->setStyleSheet("background-color: rgb(20, 20, 20); color: white");
    ui->groupBox->setStyleSheet("background-color: rgb(50, 50, 50); color: white");
    //ui->drawingBoard->setStyleSheet("background-color: rgb(20, 20, 20)");
    ui->groupBox2->setStyleSheet("background-color: rgb(50, 50, 50); color: white");
}

void View::themeWhite(){
    this->setStyleSheet("background-color: white;");
    ui->fillButton->setStyleSheet("background-color: rgb(230, 230, 230);");
    ui->penButton->setStyleSheet("background-color: rgb(230, 230, 230);");
    ui->rectangleButton->setStyleSheet("background-color: rgb(230, 230, 230);");
    ui->eraseButton->setStyleSheet("background-color: rgb(230, 230, 230);");
    ui->ellipseButton->setStyleSheet("background-color: rgb(230, 230, 230);");
    ui->cpButton->setStyleSheet("background-color: rgb(230, 230, 230); color: black");
    ui->lineButton->setStyleSheet("background-color: rgb(230, 230, 230);");
    ui->undoButton->setStyleSheet("background-color: rgb(230, 230, 230);");
    ui->redoButton->setStyleSheet("background-color: rgb(230, 230, 230);");
    ui->zoomOutButton->setStyleSheet("background-color: rgb(230, 230, 230);");
    ui->zoomInButton->setStyleSheet("background-color: rgb(230, 230, 230);");
    ui->addFrameButton->setStyleSheet("background-color: rgb(230, 230, 230); color: black");
    ui->previewscrollbar->setStyleSheet("background-color: rgb(230, 230, 230);");
    ui->mainToolBar->setStyleSheet("background-color: rgb(230, 230, 230);");
    ui->menuBar->setStyleSheet("background-color: white; color: black");
    ui->menuFile->setStyleSheet("background-color: white; color: black");
    ui->groupBox->setStyleSheet("background-color: rgb(230, 230, 230); color: black");
    //ui->groupBox2->setStyleSheet("background-color: rgb(230, 230, 230); color: black");
    ui->groupBox2->setStyleSheet("background-color: rgb(230, 230, 230); color: white");
}



View::~View()
{
    delete ui;
}

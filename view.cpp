#include "view.h"
#include "ui_view.h"


View::View(Model* m, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::View) {

    ui->setupUi(this);

    //Used to create a new sprite
    newSprite = new CreateNewSprite();
    //Used to know when to open the new sprite dialog
    connect(ui->actionNew, &QAction::triggered, this, &View::openNewSpriteWindow);


    // Connection to model to create a new sprite, and also from UI to model to open save, and export to gif.
    connect(newSprite, &CreateNewSprite::sendSpriteInfo, m, &Model::createNewSprite);
    connect(ui->actionLoad, &QAction::triggered, m, &Model::open);
    connect(ui->actionSave, &QAction::triggered, m, &Model::save);
    connect(ui->actionExport_to_Gif, &QAction::triggered, m, &Model::exportToGif);
    //Connection for model to know when to create a new board and also the drawing widget, used for resizing on new/load
    connect(m, &Model::sendNewInfo, ui->drawingBoard, &DrawingWidget::createNewBoard);


    // Connection from model to scrollbar.
    connect(m, &Model::setMaxScroll, ui->previewscrollbar, &QScrollBar::setMaximum); 
    connect(m, &Model::setScrollPosition, ui->previewscrollbar, &QScrollBar::setValue); 
    connect(ui->previewscrollbar, &QScrollBar::valueChanged, m, &Model::changeFrame);
    connect(ui->previewscrollbar, &QScrollBar::valueChanged, m, &Model::changeFramerate);




    connect(m, &Model::showColor, ui->colorButton, &QPushButton::setStyleSheet);

    //Connections for the drawing board, used to send to the model that scaling in and out
    //Highlighting a pixel...
    connect(m, &Model::sendScaleIn, ui->drawingBoard, &DrawingWidget::scaleIn);
    connect(m, &Model::sendScaleOut, ui->drawingBoard, &DrawingWidget::scaleOut);
    connect(m, &Model::sendHighlight, ui->drawingBoard, &DrawingWidget::highlightPixel);

    //Connections for drawing board to signal when a mouse event has occured, to show
    //previews, or draw images... etc.
    connect(ui->drawingBoard, &DrawingWidget::mouseMove, m, &Model::manipulateImage);
    connect(ui->drawingBoard, &DrawingWidget::unclick, m, &Model::addShapeToImage);
    // Connection to redraw the board. Model sends new image to be drawn to drawing widget.
    connect(m, &Model::redrawImage, ui->drawingBoard, &DrawingWidget::drawUpdatedImage);
    // Connection from a drawing board click to an image manipulation in the model.
    connect(ui->drawingBoard, &DrawingWidget::click, m, &Model::manipulateImage);


    //Timer for sending how often the preview should be updated depending on slider.
    frameTimer = new QTimer(this);
    connect(frameTimer, SIGNAL(timeout()), m, SLOT(frameRequested()));
    frameTimer->start(1000/ui->fpsSlider->value());
    // Changes here for preview widget....
    ui->previewWidget->scaleIn(2);


    //Preview connections. used to change fps, and add and delete frames...
    connect(ui->fpsSlider, &QSlider::valueChanged, this, &View::fpsChange);
    connect(ui->addFrameButton, &QPushButton::clicked, m, &Model::addToFrames);
    connect(ui->deleteFrameButton, &QPushButton::clicked, m, &Model::deleteFromFrames);



    //Connections for selecting all the different tools
    connect(ui->rectangleButton, &QPushButton::clicked, m, &Model::rectSelected);
    connect(ui->ellipseButton, &QPushButton::clicked, m, &Model::ellipseSelected);
    connect(ui->eraseButton, &QPushButton::clicked, m, &Model::eraseSelected);
    connect(ui->cpButton, &QPushButton::clicked, m, &Model::colorpickerSelected);
    connect(ui->penButton, &QPushButton::clicked, m, &Model::penSelected);
    connect(ui->lineButton, &QPushButton::clicked, m, &Model::lineSelected);
    connect(ui->fillButton, &QPushButton::clicked, m, &Model::fillSelected);
    //More tool connections and zooming and unzooming.
    connect(ui->zoomInButton, &QPushButton::clicked, m, &Model::scaleIn);
    connect(ui->zoomOutButton, &QPushButton::clicked, m, &Model::scaleOut);
    connect(ui->colorButton, &QPushButton::clicked, m, &Model::colorOpen);
    connect(ui->undoButton, &QPushButton::clicked, m, &Model::undoAction);
    connect(ui->redoButton, &QPushButton::clicked, m, &Model::redoAction);


    //Connectiosn to send images to preview widgets for viewing.
    connect(m, &Model::sendPreview, ui->previewWidget, &DrawingWidget::drawUpdatedImage);
    connect(m, &Model::sendPreviewMid, ui->previewWidgetMid, &DrawingWidget::drawUpdatedImage);
    connect(m, &Model::sendPreviewLeft, ui->previewWidgetLeft, &DrawingWidget::drawUpdatedImage);
    connect(m, &Model::sendPreviewRight, ui->previewWidgetRight, &DrawingWidget::drawUpdatedImage);

    //Connections to change the theme when clicked.
    connect(ui->actionDark, &QAction::triggered, this, &View::themeDark);
    connect(ui->actionLight, &QAction::triggered, this, &View::themeLight);

    // ScrollBar changes to signal drawingboard shift.
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

    QString temp = "FPS:" + QString::number(change);

    frameTimer->stop();
    frameTimer->start(1000/change);
    ui->fpsLabel->setText(temp);
}

void View::themeDark(){
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
    ui->menuFile->setStyleSheet("background-color: rgb(20, 20, 20); selection-background-color: rgb(50, 50, 50); color: white");
    ui->groupBox->setStyleSheet("background-color: rgb(50, 50, 50); color: white");
    ui->groupBox2->setStyleSheet("background-color: rgb(50, 50, 50); color: white");
}

void View::themeLight(){
    this->setStyleSheet("");
    ui->fillButton->setStyleSheet("");
    ui->penButton->setStyleSheet("");
    ui->rectangleButton->setStyleSheet("");
    ui->eraseButton->setStyleSheet("");
    ui->ellipseButton->setStyleSheet("");
    ui->cpButton->setStyleSheet("");
    ui->lineButton->setStyleSheet("");
    ui->undoButton->setStyleSheet("");
    ui->redoButton->setStyleSheet("");
    ui->zoomOutButton->setStyleSheet("");
    ui->zoomInButton->setStyleSheet("");
    ui->addFrameButton->setStyleSheet("");
    ui->previewscrollbar->setStyleSheet("");
    ui->mainToolBar->setStyleSheet("");
    ui->menuBar->setStyleSheet("");
    ui->menuFile->setStyleSheet("");
    ui->groupBox->setStyleSheet("");
    ui->groupBox2->setStyleSheet("");
}



View::~View()
{
    delete ui;
}

#include "createnewsprite.h"
#include "ui_createnewsprite.h"

CreateNewSprite::CreateNewSprite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewSpriteWindow)
{
    ui->setupUi(this);

    connect(ui->confirmButton, &QPushButton::clicked, this, &CreateNewSprite::getInfoToSend);
    connect(ui->cancelButton, &QPushButton::clicked, this, &CreateNewSprite::close);



}

void CreateNewSprite::getInfoToSend()
{
   int width = ui->widthChanger->value();
   int height = ui->heightChanger->value();

   emit sendSpriteInfo(width, height);

   this->close();
}



CreateNewSprite::~CreateNewSprite()
{
    delete ui;
}

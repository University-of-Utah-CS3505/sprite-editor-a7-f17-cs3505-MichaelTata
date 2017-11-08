#include "createnewsprite.h"
#include "ui_createnewsprite.h"

CreateNewSprite::CreateNewSprite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewSpriteWindow)
{
    ui->setupUi(this);






}

void CreateNewSprite::getInfoToSend()
{
   int width = ui->widthChanger->value();
   int height = ui->heightChanger->value();

   emit sendSpriteInfo(width, height);
}



CreateNewSprite::~CreateNewSprite()
{
    delete ui;
}

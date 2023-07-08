#include "UI_goodgame.h"
#include <QPainter>
#include <QKeyEvent>
#include <QLabel>

goodgame::goodgame(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(1080,608);
    setWindowIcon(QIcon("D:/QTProject/Celeste_Copy/Image/Strawberry.png"));
    setWindowTitle("GoodGame");
}

void goodgame::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load("D:/QTProject/Celeste_Copy/Image/goodgame.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void goodgame::switchToMainInterface(){
    this -> hide();
    emit returnToMainInterface();
}

void goodgame::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_X) {
        //qDebug()<<"返回主界面";
        PressPlayer->setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/ui_main_button_back.wav"));
        PressPlayer->setVolume(0.35f);
        PressPlayer->setLoopCount(1);
        PressPlayer->play();
        switchToMainInterface();
    }
}



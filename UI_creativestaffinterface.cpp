#include "UI_creativestaffinterface.h"
#include <QPainter>
#include <QLabel>
#include <QKeyEvent>
creativestaffinterface::creativestaffinterface(QWidget *parent)
    : QMainWindow{parent}
{
    setFixedSize(1080,608);
    setWindowIcon(QIcon("D:/QTProject/Celeste_Copy/Image/Strawberry.png"));
    setWindowTitle("creativestaff");
    setupCreativeStaffInterfaceText();
}
void creativestaffinterface::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load("D:/QTProject/Celeste_Copy/Image/staffinterface.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void creativestaffinterface::switchToMainInterface(){
    this -> hide();
    emit returnToMainInterface();
}

void creativestaffinterface::keyPressEvent(QKeyEvent *event)
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

void creativestaffinterface::setupCreativeStaffInterfaceText(){
    QFont font;
    font.setFamily("宋体");
    font.setPointSize(18);

    QLabel * option = new QLabel;
    option -> setParent(this);
    option -> setStyleSheet("color:black;");
    option -> setFont(font);
    option -> setText("       Matt Makes Games开发团队\n                 &\n        PKU2023春程序设计实习\n                28组\n王振宇  游戏元素实现  游戏地图设计\n陈明宇  游戏框架搭建  项目内容整合\n 吴锐   UI界面  图像处理  音效处理\n\n\n  本项目仅供学习交流使用，不构成商业目的。\n版权归Celeste开发团队Matt Makes Games所有。");
    option -> setGeometry(320,50,800,500);//坐标
}

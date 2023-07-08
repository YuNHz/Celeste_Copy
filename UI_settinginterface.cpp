#include "UI_settinginterface.h"
#include <QPainter>
#include <QKeyEvent>
#include <QLabel>
settinginterface::settinginterface(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(1080,608);
    setWindowIcon(QIcon("D:/QTProject/Celeste_Copy/Image/Strawberry.png"));
    setWindowTitle("setting");
    setupSettingInterfaceText();
}

void settinginterface::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load("D:/QTProject/Celeste_Copy/Image/settinginterface0.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void settinginterface::switchToMainInterface(){
    this -> hide();
    emit returnToMainInterface();
}

void settinginterface::keyPressEvent(QKeyEvent *event)
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

void settinginterface::setupSettingInterfaceText(){
    QFont font;
    font.setFamily("宋体");
    font.setPointSize(32);

    QLabel * option = new QLabel;
    option -> setParent(this);
    option -> setStyleSheet("color:blue;");
    option -> setFont(font);
    option -> setText("向左移动 ← A   向右移动 → D\n跳跃     ↑ K   冲刺     ↗ L+W+D");
    option -> setGeometry(200,25,900,570);//坐标
}


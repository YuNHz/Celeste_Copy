#include "widget.h"
#include "ui_widget.h"
#include <QTimer>
#include <QVector2D>
#include <QKeyEvent>


#include "platform.h"
#include "madeline.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(960,540);


    mGameView.setSceneRect(QRect(0,0,960,540));
    mScene.setSceneRect(QRect(0,0,960,540));
    mBackground.setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\background1.png").scaled(960,540,Qt::KeepAspectRatio));

    mScene.addItem(&mBackground);


    mScene.addItem(new Platform(20,9.0,480.0));
    mScene.addItem(&Hero);

    mGameView.setScene(&mScene);
    mGameView.setParent(this);
    mGameView.show();

    madelineTimer = new QTimer(this);
    madelineTimer->start(10);
    connect(madelineTimer,&QTimer::timeout,this,&Widget::PlaneMove);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
        case Qt::Key_W:
        case Qt::Key_S:
        case Qt::Key_A:
        case Qt::Key_D:
        mKeyList.append(event->key());
        break;
    }
}

void Widget::PlaneMove(){
    for(int keyCode:mKeyList){
        switch(keyCode){
        case Qt::Key_W: Hero.moveBy(0,-5);break;
        case Qt::Key_S: Hero.moveBy(0,5);break;
        case Qt::Key_A: Hero.moveBy(-5,0);break;
        case Qt::Key_D: Hero.moveBy(5,0);break;
        }
    }
}

void Widget::keyReleaseEvent(QKeyEvent* event){
    if(mKeyList.contains(event->key())){
        mKeyList.removeOne(event->key());
    }
}

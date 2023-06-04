#include "widget.h"
#include "ui_widget.h"
#include <QTimer>
#include <QKeyEvent>
#include "spike.h"
#include "platform.h"
#include "madeline.h"
#include <iostream>
using namespace std;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(960,540);

    mGameView.setSceneRect(QRect(0,0,960,540));
    mScene.setSceneRect(QRect(0,0,960,540));

    Game();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_A:{
            if(mKeyList.contains(Qt::Key_D)){
                mKeyList.removeOne(Qt::Key_D);
                mKeyList.append(event->key());
                break;
            }
            else{
                mKeyList.append(event->key());
                break;
            }
        }
        case Qt::Key_D:{
            if(mKeyList.contains(Qt::Key_A)){
                mKeyList.removeOne(Qt::Key_A);
                mKeyList.append(event->key());
                break;
            }
            else{
                mKeyList.append(event->key());
                break;
            }
        }
        case Qt::Key_W:     mKeyList.append(event->key());break;
        case Qt::Key_S:     mKeyList.append(event->key());break;
        case Qt::Key_C:     mKeyList.append(event->key());break;
        case Qt::Key_X:     mKeyList.append(event->key());break;
        case Qt::Key_Z:     mKeyList.append(event->key());break;
    }
}

void Widget::keyReleaseEvent(QKeyEvent* event){
    if(mKeyList.contains(event->key())){
        mKeyList.removeOne(event->key());
    }
}

void Widget::Game(){
    Map1();
    GameTimer = new QTimer(this);
    GameTimer->start(1000/60);
    connect(GameTimer,&QTimer::timeout,this,[this](){
        Hero->operate(mKeyList);
//        Collosion();
        if(Hero->isDead()){
            GameTimer->stop();
            QTimer * timer = new QTimer;
            timer->start(50);
            connect(timer,&QTimer::timeout,this,[&](){
                if(Hero->grap<5) Hero->deadGraphics();
                else{
                    timer->stop();
                }
            });
        }
    });
}

void Widget::Collosion(){
            cout<<Hero->boundingRect().x()<<"    "<<Hero->boundingRect().y()<<endl;
    for(auto it:Map){
        cout<<Hero->Box().intersects(it->boundingRect())<<endl;
        if(Hero->Box().intersects(it->boundingRect())){
            if(it->boundingRect().height()==21||it->boundingRect().width()==21){
                    cout<<"12345678"<<endl;
                Hero->die();
            }
            else{
                cout<<"12345678"<<endl;
                Hero->y = it->y()-48;
            }
        }
    }
}

void Widget::Map1(){
    mBackground.setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\backgroundT.png").scaled(960,540,Qt::KeepAspectRatio));
    mScene.addItem(&mBackground);

    Hero = new Madeline(24,540-120-48,0);

    Platform * PlatformP;
    Spike * SpikeP;

//    PlatformP = new Platform(5,0.0,540.0-24.0*5,0);
//    Map.append(PlatformP);
//    PlatformP = new Platform(5,120.0,540.0-24.0*2,0);
//    Map.append(PlatformP);
//    PlatformP = new Platform(3,240.0,540.0-24.0*7,0);
//    Map.append(PlatformP);
//    PlatformP = new Platform(5,312.0,540.0-24.0*4,0);
//    Map.append(PlatformP);
//    PlatformP = new Platform(3,432.0,540.0-24.0*13,0);
//    Map.append(PlatformP);
//    PlatformP = new Platform(4,528.0,540.0-24.0*7,0);
//    Map.append(PlatformP);
//    PlatformP = new Platform(3,432.0,540.0-24.0*13,0);
//    Map.append(PlatformP);
//    PlatformP = new Platform(4,528.0,540.0-24.0*7,0);
//    Map.append(PlatformP);
//    PlatformP = new Platform(3,624.0,540.0-24.0*3,0);
//    Map.append(PlatformP);
//    PlatformP = new Platform(5,744.0,540.0-24.0*16,0);
//    Map.append(PlatformP);
//    PlatformP = new Platform(2,864.0,540.0-24.0*21,0);
//    Map.append(PlatformP);

    SpikeP = new Spike(5,120.0,540-(48.0+21.0),0);
    Map.append(SpikeP);
    SpikeP = new Spike(5,312.0,540-(24.0*4+21.0),0);
    Map.append(SpikeP);
    SpikeP = new Spike(4,528.0,540-(24.0*7+21.0),0);
    Map.append(SpikeP);
    SpikeP = new Spike(3,624.0,540-(24.0*3+21.0),0);
    Map.append(SpikeP);

    for(auto it:Map){
        mScene.addItem(it);
    }

    mScene.addItem(Hero);
    mGameView.setScene(&mScene);
    mGameView.setParent(this);
    mGameView.show();

    if(first){
        backGroundMusic.setSource(QUrl::fromLocalFile("D:/QTProject/Celeste_Copy/Music/mus_lvl2_badeline_loop.wav"));
        backGroundMusic.setLoopCount(QSoundEffect::Infinite);
        backGroundMusic.play();
        first = false;
    }
}

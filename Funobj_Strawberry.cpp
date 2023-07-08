#include "Funobj_Strawberry.h"

Strawberry::Strawberry(QPointF pos, QObject* parent)
    : Funobj { pos, QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Strawberry1.png").scaled(Strawberry::length, Strawberry::width), parent }
{
    connect(StrawberryTimer,&QTimer::timeout,this,&Strawberry::graphic);
}

void Strawberry::graphic(){
    graphicCnt += 1;
    if(graphicCnt>4) graphicCnt = 1;
    switch(graphicCnt){
    case 1:setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Strawberry1.png").scaled(length, width));
        break;
    case 2:setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Strawberry2.png").scaled(length, width));
        break;
    case 3:setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Strawberry3.png").scaled(length, width));
        break;
    case 4:setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Strawberry4.png").scaled(length, width));
        break;
    }
}

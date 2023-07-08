#include "Obstacle_Spike.h"

Spike::Spike(QPointF pos, int direct, QObject* parent)
    : Obstacle { pos, QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Spike1.png").scaled(length, width), parent },direct(direct)
{
    switch(direct){
    case 1:
        setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Spike1.png").scaled(length, width));
        break;
    case 2:
        setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Spike2.png").scaled(length, width));
        break;
    case 3:
        setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Spike3.png").scaled(width, length));
        break;
    case 4:
        setPixmap(QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Spike4.png").scaled(width, length));
        break;
    }
}

#include "Obstacle_Dream.h"

Dream::Dream(QPointF pos, QObject* parent)
    : Obstacle { pos, QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Dream.png").scaled(length, width), parent }
{
}

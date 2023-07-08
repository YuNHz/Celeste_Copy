#include "Obstacle_Platform.h"

Platform::Platform(QPointF pos, QObject* parent)
    : Obstacle { pos, QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Platform.png").scaled(length, width), parent }
{
}

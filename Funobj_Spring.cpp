#include "Funobj_Spring.h"

Spring::Spring(QPointF pos, QObject* parent)
    : Funobj { pos, QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\Spring1.png").scaled(length, width), parent }
{
}

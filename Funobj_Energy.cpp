#include "Funobj_Energy.h"

Energy::Energy(QPointF pos, QObject* parent)
    : Funobj { pos, QPixmap("D:\\QTProject\\Celeste_Copy\\Image\\energy.png").scaled(length, width), parent }
{
}

#include "Obstacle.h"

Obstacle::Obstacle(QPointF pos, const QPixmap& image, QObject* parent)
    : GameRectFItem { pos, image, parent }
{
}
